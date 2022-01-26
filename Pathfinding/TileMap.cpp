#include "TileMap.h"

using namespace AI;

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

void TileMap::Load(const std::filesystem::path& mapFileName, const char* textureFileName)
{
	LoadTextures(textureFileName);
	LoadMap(mapFileName);
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

	mGraph.Initialize(mColumns, mRows);

	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			if (IsBlocked(c, r))
				continue;

			auto GetNeighbour = [&](int c, int r) -> AI::GridBasedGraph::Node*
			{
				//const GridBasedGraph::Node* node = mGraph.GetNode(c, r);
				const auto node = mGraph.GetNode(c, r);
				if (node == nullptr)
					return nullptr;

				if (IsBlocked(c, r))
					return nullptr;

				return node;
			};

			GridBasedGraph::Node* node = mGraph.GetNode(c, r);

			node->neighbours[GridBasedGraph::North] = GetNeighbour(c, r - 1);
			node->neighbours[GridBasedGraph::South] = GetNeighbour(c, r + 1);
			node->neighbours[GridBasedGraph::East] = GetNeighbour(c + 1, r);
			node->neighbours[GridBasedGraph::West] = GetNeighbour(c - 1, r);
			node->neighbours[GridBasedGraph::NorthEast] = GetNeighbour(c + 1, r - 1);
			node->neighbours[GridBasedGraph::NorthWest] = GetNeighbour(c - 1, r - 1);
			node->neighbours[GridBasedGraph::SouthEast] = GetNeighbour(c + 1, r + 1);
			node->neighbours[GridBasedGraph::SouthWest] = GetNeighbour(c - 1, r + 1);
		}
	}

	// Make double for loop to connect node to neighbours
	//mGraph.GetNode(4,5)->neighbours[GridBasedGraph::East] = mGraph.GetNode(5,5)
	// Use the IsBlocked function to see if it should be added
}

void TileMap::LoadTextures(const char* fileName)
{
	if (!std::filesystem::exists(fileName))
		return;

	std::ifstream file(fileName);

	int count = 0;
	std::string buffer;

	file >> buffer;
	file >> count;

	mTiles.clear();
	mTiles.reserve(count);
	mBlocked.clear();
	mBlocked.reserve(count);

	for (int i = 0; i < count; ++i)
	{
		int blocked = 0;
		file >> buffer;
		file >> blocked;
		mTiles.push_back(X::LoadTexture(buffer.c_str()));
		mBlocked.push_back(blocked == 1);
	}

	file.close();

	mTileWidth = X::GetSpriteWidth(mTiles.front());
	mTileHeight = X::GetSpriteHeight(mTiles.front());
}

void TileMap::Update(float deltaTime)
{
}

void TileMap::Render()
{
	int x, y, index = 0;
	X::Math::Vector2 pos;

	for (pos.y = 0.0f, y = 0; y < mRows; ++y, pos.y += mTileWidth)
	{
		for (x = 0, pos.x = 0.0f; x < mColumns; ++x, pos.x += mTileHeight)
		{
			const auto tileIndex = mMap[index++];
			const auto tileId = mTiles[tileIndex];
			X::DrawSprite(tileId, pos, 0.0f, X::Pivot::TopLeft);
		}
	}

	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			const auto node = mGraph.GetNode(c, r);
			for (const auto neighbor : node->neighbours)
			{
				if (neighbor == nullptr)
					continue;

				const auto a = GetPixelPosition(node->column, node->row);
				const auto b = GetPixelPosition(neighbor->column, neighbor->row);
				X::DrawScreenLine(a, b, X::Colors::Blue);
			}
		}
	}
	// TODO - Use X::DrawScreenLine to visualize the graph
}

void TileMap::Unload()
{
	mColumns = 0;
	mRows = 0;
	mMap.clear();
	mTiles.clear();
}

X::Math::Vector2 TileMap::GetPixelPosition(int x, int y) const
{
	return
	{
		(x + 0.5f) * mTileWidth,
		(y + 0.5f) * mTileHeight
	};
}

bool TileMap::IsBlocked(int x, int y) const
{
	const int tile = mMap[GetIndex(x, y)];
	const bool blocked = mBlocked[tile];
	return blocked;
}

int TileMap::GetIndex(int column, int row) const
{
	return column + (row * mColumns);
}

std::vector<X::Math::Vector2> TileMap::FindPathBFS(int startX, int startY, int endX, int endY)
{
	std::vector<X::Math::Vector2> path;

	BFS bfs;
	if (bfs.Run(mGraph, startX, startY, endX, endY))
	{
		const auto& closedList = bfs.GetClosedList();
		auto node = closedList.back();
		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());

		// Cache the closed list for visualization
		mClosedList = closedList;
	}

	return path;
}