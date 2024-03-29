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

	void Load(const std::filesystem::path& mapFileName, const char* textureFileName);
	void Unload();
	void Update(float deltaTime);
	void Render();


	bool IsBlocked(int x, int y) const;

	std::vector<X::Math::Vector2> FindPathBFS(int startX, int startY, int endX, int endY);
	std::vector<X::Math::Vector2> FindPathDFS(int startX, int startY, int endX, int endY);
	std::vector<X::Math::Vector2> FindPathDijkastra(int startX, int startY, int endX, int endY);
	std::vector<X::Math::Vector2> FindPathAStar(int startX, int startY, int endX, int endY);

	const int GetRows() const { return mRows; }
	const int GetColumns() const { return mColumns; }
	X::Math::Vector2 GetPixelPosition(int x, int y) const;

private:
	void LoadMap(const std::filesystem::path& fileName);
	void LoadTextures(const char* fileName);
	int GetIndex(int column, int row) const;
	float GetCost(const AI::GridBasedGraph::Node* nodeA, const AI::GridBasedGraph::Node* nodeB) const;
	float GetHeuristic(const AI::GridBasedGraph::Node* nodeA, const int endX, const int endY) const;

	AI::GridBasedGraph mGraph;
	AI::NodeList mClosedList;
	std::vector<int> mMap;
	std::vector<X::TextureId> mTiles; // I forgot to add this in class
	std::vector<bool> mBlocked;
	int mColumns = 0;
	int mRows = 0;
	int mTileWidth = 0;
	int mTileHeight = 0;
};