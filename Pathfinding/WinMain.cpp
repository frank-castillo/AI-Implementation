#include "TileMap.h"
#include "PathMethods.h"
#include <XEngine.h> // <> for external includes, "" for internal includes

int startX = 8;
int startY = 4;
int endX = 28;
int endY = 15;
std::vector<X::Math::Vector2> path;

PathMethod method = PathMethod::None;

//--------------------------------------------------
void DrawLocation(int x, int y, X::Color color)
{
	const auto pos = TileMap::Get().GetPixelPosition(x, y);
	for (int i = 0; i < 5; ++i)
		X::DrawScreenCircle(pos, 10.0f + (i * 1.0f), color);
}

void GameInit()
{
	TileMap::Initialize();
	TileMap::Get().Load("map.txt", "tiles.txt");
}

bool GameLoop(float deltaTime)
{
	TileMap::Get().Render();

	// Start Point Control
	if (X::IsKeyPressed(X::Keys::W))
		startY -= 1;
	if (X::IsKeyPressed(X::Keys::S))
		startY += 1;
	if (X::IsKeyPressed(X::Keys::A))
		startX -= 1;
	if (X::IsKeyPressed(X::Keys::D))
		startX += 1;

	// End Point Control
	if (X::IsKeyPressed(X::Keys::UP))
		endY -= 1;
	if (X::IsKeyPressed(X::Keys::DOWN))
		endY += 1;
	if (X::IsKeyPressed(X::Keys::LEFT))
		endX -= 1;
	if (X::IsKeyPressed(X::Keys::RIGHT))
		endX += 1;

	if (X::IsKeyPressed(X::Keys::ONE) || method == PathMethod::BFS)
		path = TileMap::Get().FindPathBFS(startX, startY, endX, endY),
		method = PathMethod::BFS;
	if (X::IsKeyPressed(X::Keys::TWO) || method == PathMethod::DFS)
		path = TileMap::Get().FindPathDFS(startX, startY, endX, endY),
		method = PathMethod::DFS;
	if (X::IsKeyPressed(X::Keys::THREE) || method == PathMethod::Dijkastra)
		path = TileMap::Get().FindPathDijkastra(startX, startY, endX, endY),
		method = PathMethod::Dijkastra;
	if (X::IsKeyPressed(X::Keys::FOUR) || method == PathMethod::ASTAR)
		path = TileMap::Get().FindPathAStar(startX, startY, endX, endY),
		method = PathMethod::ASTAR;

	// Draw line connecting the nodes from the path we get from our search
	for (int i = 0; i + 1 < path.size(); ++i)
	{
		const auto a = path[i];
		const auto b = path[i + 1];
		const auto offset = X::Math::Vector2(1.0f, 0.0f);
		X::DrawScreenLine(a, b, X::Colors::Red);
		X::DrawScreenLine(a + offset, b + offset, X::Colors::Red);
	}
	DrawLocation(startX, startY,X::Colors::Red);
	DrawLocation(endX, endY,X::Colors::Yellow);

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	TileMap::Get().Unload();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Pathfinding");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}

