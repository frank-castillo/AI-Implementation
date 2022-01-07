#pragma once

#include <XEngine.h>

class TileMap
{
public:
	// Singleton method
	static void Initialize();
	static void Terminate();
	static TileMap& Get();

	void Load(const std::filesystem::path& mapFileName, const std::filesystem::path& textureFileName);
	void Unload();
	void Update(float deltaTime);
	void Render();

private:
	void LoadMap(const std::filesystem::path& fileName);
	void LoadTextures(const std::filesystem::path& fileName);
	int GetIndex(int column, int row) const;

	std::vector<int> mMap;
	std::vector<X::TextureId> mTiles; // I forgot to add this in class
	int mColumns = 0;
	int mRows = 0;
};