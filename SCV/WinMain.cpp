#include "SCV.h"

AI::AIWorld aiWorld;
std::vector<std::unique_ptr<SCV>> scvs;

void GameInit()
{
	for (int i = 0; i < 2; ++i)
	{
		auto& scv = scvs.emplace_back(std::make_unique<SCV>(aiWorld));
		scv->Load();

		if (i == 0)
		{
			scv->ShowDebug(true);
		}
		
		scv->position = X::RandomVector2({ 100.0f, 100.0f }, { 1180.0f, 620.0f });
	}
}

bool GameLoop(float deltaTime)
{
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		const float mouseX = static_cast<float>(X::GetMouseScreenX());
		const float mouseY = static_cast<float>(X::GetMouseScreenY());
		scvs[0]->destination = X::Math::Vector2(mouseX, mouseY);
	}

	if (X::IsKeyPressed(X::Keys::ONE))
	{
		scvs[0]->SetSeek(true);
		scvs[0]->SetFlee(false);
		scvs[0]->SetArrive(false);
		scvs[0]->SetPursuit(false);
	}

	if (X::IsKeyPressed(X::Keys::TWO))
	{
		scvs[0]->SetSeek(false);
		scvs[0]->SetFlee(true);
		scvs[0]->SetArrive(false);
		scvs[0]->SetPursuit(false);
	}

	if (X::IsKeyPressed(X::Keys::THREE))
	{
		scvs[0]->SetSeek(false);
		scvs[0]->SetFlee(false);
		scvs[0]->SetArrive(true);
		scvs[0]->SetPursuit(false);
	}

	if (X::IsKeyPressed(X::Keys::FOUR))
	{
		scvs[1]->SetSeek(false);
		scvs[1]->SetFlee(false);
		scvs[1]->SetArrive(false);
		scvs[1]->SetPursuit(true);
		//scvs[1]->
	}

	for (auto& scv : scvs)
		scv->Update(deltaTime);
	for (auto& scv : scvs)
		scv->Render();

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	for (auto& scv : scvs)
		scv->Unload();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Steering");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}