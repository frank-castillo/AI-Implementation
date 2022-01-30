#include "TileMap.h"
#include <XEngine.h> // <> for external includes, "" for internal includes

X::TextureId textureId;
X::Math::Vector2 position;
int startX = 8;
int startY = 4;
int endX = 20;
int endY = 15;
std::vector<X::Math::Vector2> path;

//--------------------------------------------------

void GameInit()
{
	TileMap::Initialize();
	TileMap::Get().Load("map.txt", "tiles.txt");
}

bool GameLoop(float deltaTime)
{
	TileMap::Get().Render();

	if (X::IsKeyPressed(X::Keys::ONE))
		path = TileMap::Get().FindPathBFS(startX, startY, endX, endY);

	for (int i = 0; i + 1 < path.size(); ++i)
	{
		const auto a = path[i];
		const auto b = path[i + 1];
		X::DrawScreenLine(a, b, X::Colors::White);
	}
	X::DrawScreenCircle(TileMap::Get().GetPixelPosition(startX, startY), 10.0f, X::Colors::Red);
	X::DrawScreenCircle(TileMap::Get().GetPixelPosition(endX, endY), 10.0f, X::Colors::Yellow);

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

