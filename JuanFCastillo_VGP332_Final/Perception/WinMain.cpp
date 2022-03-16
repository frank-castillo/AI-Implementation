#include "Mineral.h"
#include "SCV.h"
#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

AI::AIWorld world;
std::vector<std::unique_ptr<SCV>> scvs;
std::vector<std::unique_ptr<Mineral>> minerals;

// Tuning
float viewRange = 300.0f;
float viewAngle = 45.0f;
float wanderJitter = 1.0f;
float wanderRadius = 50.0f;
float wanderDistance = 100.0f;
bool pause = false;
bool debug = false;

void DrawUI()
{
	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::CollapsingHeader("Visual Sensor"))
	{
		ImGui::DragFloat("View Range##SCV", &viewRange, 1.0f, 100.0f, 1000.0f);
		ImGui::DragFloat("View Angle##SCV", &viewAngle, 1.0f, 10.0f, 180.0f);
	}

	if (ImGui::CollapsingHeader("Wander Behavior"))
	{
		ImGui::DragFloat("Jitter", &wanderJitter, 0.1f, 1.0f, 10.0f);
		ImGui::DragFloat("Radius", &wanderRadius, 0.1f, 1.0f, 1000.0f);
		ImGui::DragFloat("Distance", &wanderDistance, 0.1f, 1.0f, 1000.0f);
	}

	ImGui::Checkbox("Pause", &pause);

	if (ImGui::Checkbox("Debug", &debug))
	{
		for (auto& scv : scvs)
			scv->SetDebug(debug);
	}

	ImGui::End();
}

void GameInit()
{
	// Setup world
	world.AddObstacle({ 230.0f, 300.0f, 50.0f });

	X::Math::Vector2 topLeft(500.0f, 100.0f);
	X::Math::Vector2 topRight(600.0f, 100.0f);
	X::Math::Vector2 bottomLeft(500.0f, 600.0f);
	X::Math::Vector2 bottomRight(600.0f, 600.0f);
	world.AddWall({ topLeft, topRight });
	world.AddWall({ topRight, bottomRight });
	world.AddWall({ bottomRight, bottomLeft });
	world.AddWall({ bottomLeft, topLeft });

	for (int i = 0; i < 1; ++i)
	{
		auto& scv = scvs.emplace_back(std::make_unique<SCV>(world));
		scv->Initialize();
		scv->SetWander(true);
		scv->position.x = X::RandomFloat(100.0f, 900.0f);
		scv->position.y = X::RandomFloat(100.0f, 600.0f);
	}

	for (int i = 0; i < 10; ++i)
	{
		auto& mineral = minerals.emplace_back(std::make_unique<Mineral>(world));
		mineral->Initialize();
	}
}

bool GameLoop(float deltaTime)
{
	if (pause)
		deltaTime = 0.0f;

	for (auto& scv : scvs)
		scv->Update(deltaTime);

	// Draws AI world
	for (auto& obstacle : world.GetObstacles())
		X::DrawScreenCircle(obstacle, X::Colors::White);
	for (auto& wall : world.GetWalls())
		X::DrawScreenLine(wall.from, wall.to, X::Colors::Green);

	for (auto& m : minerals)
		m->Render();
	for (auto& scv : scvs)
		scv->Render();

	DrawUI();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}