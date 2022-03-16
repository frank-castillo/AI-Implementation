#include "SCV.h"
#include <ImGui/Inc/imgui.h>

AI::AIWorld aiWorld;
std::vector<std::unique_ptr<SCV>> scvs;

float wanderJitter = 5.0f;
float wanderRadius = 20.0f;
float wanderDistance = 50.0f;
float alignmentWeight = 1.0f;
float cohesionWeight = 1.0f;
float separationWeight = 1.0f;
float alignmentMultiplier = 1.0f;
float cohesionMultiplier = 1.0f;
float separationMultiplier = 1.0f;
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
	if (ImGui::CollapsingHeader("Flock##Header", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Alignment Weight", &alignmentWeight, 0.1f, 0.0f, 500.0f);
		ImGui::DragFloat("Cohesion Weight", &cohesionWeight, 1.0f, 0.0f, 500.0f);
		ImGui::DragFloat("Separation Weight ", &separationWeight, 1.0f, 0.0f, 500.0f);
	}
	if (ImGui::CollapsingHeader("Behaviour Multipliers##Header", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Alignment multiplier", &alignmentMultiplier, 0.1f, 0.0f, 500.0f);
		ImGui::DragFloat("Cohesion multiplier", &cohesionMultiplier, 1.0f, 0.0f, 500.0f);
		ImGui::DragFloat("Separation multiplier ", &separationMultiplier, 1.0f, 0.0f, 500.0f);
	}
	if (ImGui::CollapsingHeader("Behaviours", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::Button("Wander"))
		{
			for (auto& scv : scvs)
			{
				scv->SetAlignment(false);
				scv->SetCohesion(false);
				scv->SetSeparation(false);
				scv->SetWander(true);
			}
		}
		if (ImGui::Button("Flock"))
		{
			for (auto& scv : scvs)
			{
				scv->SetAlignment(true);
				scv->SetCohesion(true);
				scv->SetSeparation(true);
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
	// Refresh neighbours list
	for (auto& scv : scvs)
	{
		scv->neighbours.clear();
	}
	for (int i = 0; i < scvs.size(); ++i)
	{
		auto& a = scvs[i];
		for (int j = i + 1; j < scvs.size(); ++j)
		{
			auto& b = scvs[j];
			if (X::Math::DistanceSqr(a->position, b->position) < X::Math::Sqr(100.0f));
			{
				a->neighbours.push_back(b.get());
				b->neighbours.push_back(a.get());
			}
		}
	}

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