#include "TileMap.h"

namespace
{
	constexpr float TILE_SIZE = 32.0f;
	std::unique_ptr<TileMap> tileMapInstance;
}

// 2D map - 5 columns x 4 rows
// [0][0][0][0][0]
// [0][0][0][0][0]
// [0][0][0][X][0]   X is at (3, 2)
// [0][0][0][0][0]

// Stored as 1D - 5x4 = 20 slots
// [0][0][0][0][0] [0][0][0][0][0] [0][0][0][X][0] [0][0][0][0][0]
//
// index = column + (row * columnCount)
//       = 3 + (2 * 5)
//       = 13

void TileMap::Initialize()
{
	XASSERT(tileMapInstance == nullptr, "TileMap already initialized");
	tileMapInstance = std::make_unique<TileMap>();
}

void TileMap::Terminate()
{
	tileMapInstance.reset();
}

TileMap& TileMap::Get()
{
	XASSERT(tileMapInstance != nullptr, "TileMap not yet created, must call Initialize() first.");
	return *tileMapInstance;
}

void TileMap::Load(const std::filesystem::path& mapFileName, const std::filesystem::path& textureFileName)
{
	LoadMap(mapFileName);
	LoadTextures(textureFileName);
}

void TileMap::Unload()
{
	mColumns = 0;
	mRows = 0;
	mMap.clear();
	mTiles.clear();
}

void TileMap::Update(float deltaTime)
{
}

void TileMap::Render()
{
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int mapIndex = GetIndex(x, y);
			const int tileIndex = mMap[mapIndex];
			const X::TextureId textureId = mTiles[tileIndex];
			const X::Math::Vector2 worldPosition = { x * TILE_SIZE, y * TILE_SIZE };
			X::DrawSprite(textureId, worldPosition, X::Pivot::TopLeft);
		}
	}
}

void TileMap::LoadMap(const std::filesystem::path& fileName)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");
	XASSERT(file, "File not opened correctly. Did you spell the filename correctly?");
	if (file)
	{
		fscanf_s(file, "Columns: %d\n", &mColumns);
		fscanf_s(file, "Rows: %d\n", &mRows);

		mMap.clear();
		for (int y = 0; y < mRows; ++y)
		{
			for (int x = 0; x < mColumns; ++x)
			{
				const int value = fgetc(file) - '0';
				mMap.push_back(value);
			}

			//This gets the end of file character out of the way "\n"
			fgetc(file);
		}

		fclose(file);
	}
}

void TileMap::LoadTextures(const std::filesystem::path& fileName)
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	XASSERT(file, "File not opened correctly. Did you spell the filename correctly?");
	if (file)
	{
		int count = 0;

		fscanf_s(file, "Count: %d\n", &count);

		mTiles.clear();
		for (int i = 0; i < count; ++i)
		{
			char buffer[256];
			fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));

			mTiles.push_back(X::LoadTexture(buffer));
		}
	}
}

int TileMap::GetIndex(int column, int row) const
{
	return column + (row * mColumns);
}
