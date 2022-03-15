#include "SCV.h"
#include <ImGui/Inc/imgui.h>

AI::AIWorld aiWorld;
std::vector<std::unique_ptr<SCV>> scvs;

float wanderJitter = 5.0f;
float wanderRadius = 20.0f;
float wanderDistance = 50.0f;
bool showDebug = true;

void SpawnSCV()
{
	auto& scv = scvs.emplace_back(std::make_unique<SCV>(aiWorld));
	scv->Load();
	scv->ShowDebug(showDebug);
	scv->position = X::RandomVector2({ 100.0f, 100.0f }, { 1180.0f, 620.0f });
}

void KillSCV()
{
	auto& scv = scvs.back();
	scv->Unload();
	scvs.pop_back();
}

void ShowTuning()
{
	ImGui::Begin("Steering Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Wander##Header", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Wander Jitter", &wanderJitter, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat("Wander Radius", &wanderRadius, 1.0f, 0.0f, 100.0f);
		ImGui::DragFloat("Wander Distance", &wanderDistance, 1.0f, 0.0f, 500.0f);
	}
	if (ImGui::CollapsingHeader("Behaviours", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::Button("Seek"))
		{
			for (auto& scv : scvs)
			{
				scv->SetSeek(true);
				scv->SetFlee(false);
				scv->SetArrive(false);
				scv->SetPursuit(false);
				scv->SetWander(false);
			}
		}
		if (ImGui::Button("Flee"))
		{
			for (auto& scv : scvs)
			{
				scv->SetSeek(false);
				scv->SetFlee(true);
				scv->SetArrive(false);
				scv->SetPursuit(false);
				scv->SetWander(false);
			}
		}
		if (ImGui::Button("Arrive"))
		{
			for (auto& scv : scvs)
			{
				scv->SetSeek(false);
				scv->SetFlee(false);
				scv->SetArrive(true);
				scv->SetPursuit(false);
				scv->SetWander(false);
			}
		}
		if (ImGui::Button("Pursuit"))
		{
			for (auto& scv : scvs)
			{
				scv->SetSeek(false);
				scv->SetFlee(false);
				scv->SetArrive(false);
				scv->SetPursuit(true);
				scv->SetWander(false);
			}
		}
		if (ImGui::Button("Wander"))
		{
			for (auto& scv : scvs)
			{
				scv->SetSeek(false);
				scv->SetFlee(false);
				scv->SetArrive(false);
				scv->SetPursuit(false);
				scv->SetWander(true);
			}
		}

	}

	ImGui::Separator();

	if (ImGui::Button("Spawn"))
	{
		SpawnSCV();
	}
	if (ImGui::Button("Kill"))
	{
		KillSCV();
	}

	ImGui::Separator();

	if (ImGui::Checkbox("Show Debug", &showDebug))
	{
		for (auto& scv : scvs)
		{
			scv->ShowDebug(showDebug);
		}
	}
	ImGui::End();
}

void GameInit()
{
	SpawnSCV();
}

bool GameLoop(float deltaTime)
{
	ShowTuning();

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		const auto mouseX = static_cast<float>(X::GetMouseScreenX());
		const auto mouseY = static_cast<float>(X::GetMouseScreenY());
		for (auto& scv : scvs)
		{
			scv->destination = X::Math::Vector2(mouseX, mouseY);
		}
	}

	if (X::IsKeyPressed(X::Keys::ONE))
	{
		scvs[0]->SetSeek(true);
		scvs[0]->SetFlee(false);
		scvs[0]->SetArrive(false);
		scvs[0]->SetPursuit(false);
		scvs[0]->SetWander(false);

	}

	if (X::IsKeyPressed(X::Keys::TWO))
	{
		scvs[0]->SetSeek(false);
		scvs[0]->SetFlee(true);
		scvs[0]->SetArrive(false);
		scvs[0]->SetPursuit(false);
		scvs[0]->SetWander(false);
	}

	if (X::IsKeyPressed(X::Keys::THREE))
	{
		scvs[0]->SetSeek(false);
		scvs[0]->SetFlee(false);
		scvs[0]->SetArrive(true);
		scvs[0]->SetPursuit(false);
		scvs[0]->SetWander(false);
	}

	if (X::IsKeyPressed(X::Keys::FOUR))
	{
		scvs[0]->SetSeek(false);
		scvs[0]->SetFlee(false);
		scvs[0]->SetArrive(false);
		scvs[0]->SetPursuit(true);
		scvs[0]->SetWander(false);
	}

	if (X::IsKeyPressed(X::Keys::FIVE))
	{
		scvs[0]->SetSeek(false);
		scvs[0]->SetFlee(false);
		scvs[0]->SetArrive(false);
		scvs[0]->SetPursuit(false);
		scvs[0]->SetWander(true);
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