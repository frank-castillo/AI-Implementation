#pragma once

#include <AI.h>
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

	bool IsBlocked(int x, int y) const;

private:
	void LoadMap(const std::filesystem::path& fileName);
	void LoadTextures(const std::filesystem::path& fileName);
	int GetIndex(int column, int row) const;

	AI::GridBasedGraph mGraph;
	std::vector<int> mMap;
	std::vector<X::TextureId> mTiles; // I forgot to add this in class
	std::vector<bool> mBlocked;
	int mColumns = 0;
	int mRows = 0;
};