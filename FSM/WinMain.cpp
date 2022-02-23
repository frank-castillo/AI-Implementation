#include <AI.h>
#include <XEngine.h>

#include "Zombie.h"
#include "Survivor.h"

AI::AIWorld aiWorld;
std::unique_ptr<Survivor> survivor;
std::vector<std::unique_ptr<Zombie>> zombies;

void GameInit()
{
	survivor = std::make_unique<Survivor>(aiWorld);
	survivor->Load();

	for (int i = 0; i < 5; ++i)
	{
		auto& newZombie = zombies.emplace_back(std::make_unique<Zombie>(aiWorld));
		newZombie->Load();
		newZombie->position = X::RandomVector2({ 100.0f, 100.0f }, { 1180.0f, 620.0f });
	}
}

bool GameLoop(float deltaTime)
{
	survivor->Update(deltaTime);

	for (auto& zombie : zombies)
		zombie->Update(deltaTime),
		zombie->Render();

	survivor->Render();

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	survivor->Unload();

	for (auto& zombie : zombies)
		zombie->Unload();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("FSM");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}

