#include <AI.h>
#include <ImGui/Inc/imgui.h>
#include <XEngine.h>

#include "FinalSurvivor.h"
#include "FinalZombie.h"
#include "FinalAmmoBox.h"

AI::AIWorld aiWorld;
std::unique_ptr<Survivor> survivor;
std::vector<std::unique_ptr<Zombie>> zombies;

constexpr int MAX_BOXES = 10;
int currentBoxIndex;
std::vector<std::unique_ptr<AmmoBox>> ammoBoxes;

// Tuning
float viewRange = 300.0f;
float viewAngle = 45.0f;
float playerWanderJitter = 3.0f;
float playerWanderRadius = 26.0f;
float playerWanderDistance = 130.0f;
float zombieWanderJitter = 3.0f;
float zombieWanderRadius = 26.0f;
float zombieWanderDistance = 130.0f;
float ammoSpawnTime = 10.f;
bool pause = false;
bool debug = true;

void DrawUI();
void SpawnAmmoBox();
void CheckAmmoBoxCollision();

void GameInit()
{
	survivor = std::make_unique<Survivor>(aiWorld);
	survivor->Load();
	survivor->SetWander(true);

	for (int i = 0; i < 5; ++i)
	{
		auto& zombie = zombies.emplace_back(std::make_unique<Zombie>(aiWorld));
		zombie->Load();
		zombie->SetWander(true);
	}

	for (int i = 0; i < MAX_BOXES; ++i)
	{
		auto& ammoBox = ammoBoxes.emplace_back(std::make_unique<AmmoBox>(aiWorld));
		ammoBox->Initialize();
	}
}

bool GameLoop(float deltaTime)
{
	if (pause)
		deltaTime = 0.0f;

	survivor->Update(deltaTime);

	for (auto& zombie : zombies)
		zombie->Update(deltaTime);

	for (auto& ammoBox : ammoBoxes)
	{
		ammoBox->Render();
	}

	ammoSpawnTime -= deltaTime;
	if (ammoSpawnTime <= 0)
	{
		SpawnAmmoBox();
		ammoSpawnTime = 30.0f;
	}

	survivor->Render();
	for (auto& zombie : zombies)
		zombie->Render();

	CheckAmmoBoxCollision();

	DrawUI();

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{

}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Final");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}

void DrawUI()
{
	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::CollapsingHeader("Visual Sensor"))
	{
		ImGui::DragFloat("View Range##SCV", &viewRange, 1.0f, 100.0f, 1000.0f);
		ImGui::DragFloat("View Angle##SCV", &viewAngle, 1.0f, 10.0f, 180.0f);
	}

	if (ImGui::CollapsingHeader("Player's Wander Behavior"))
	{
		ImGui::DragFloat("Player's Jitter", &playerWanderJitter, 0.1f, 1.0f, 10.0f);
		ImGui::DragFloat("Player's Radius", &playerWanderRadius, 0.1f, 1.0f, 1000.0f);
		ImGui::DragFloat("Player's Distance", &playerWanderDistance, 0.1f, 1.0f, 1000.0f);
	}

	if (ImGui::CollapsingHeader("Zombies' Wander Behavior"))
	{
		ImGui::DragFloat("Zombies' Jitter", &zombieWanderJitter, 0.1f, 1.0f, 10.0f);
		ImGui::DragFloat("Zombies' Radius", &zombieWanderRadius, 0.1f, 1.0f, 1000.0f);
		ImGui::DragFloat("Zombies' Distance", &zombieWanderDistance, 0.1f, 1.0f, 1000.0f);
	}

	if (ImGui::CollapsingHeader("Ammo Spawn"))
	{
		ImGui::DragFloat("Spawn Time", &ammoSpawnTime, 0.0f, .1f, 60.0f);
	}

	ImGui::Checkbox("Pause", &pause);

	if (ImGui::Checkbox("Debug", &debug))
	{
		survivor->SetDebug(debug);
		for (auto& zombie : zombies)
		{
			zombie->ShowDebug(debug);
		}
	}

	ImGui::End();
}

void SpawnAmmoBox()
{
	if (!ammoBoxes[currentBoxIndex]->IsActive())
	{
		ammoBoxes[currentBoxIndex]->RandomizeLocation();
		++currentBoxIndex;
		currentBoxIndex %= MAX_BOXES;
	}
}

void CheckAmmoBoxCollision()
{
	for (auto& ammoBox : ammoBoxes)
	{
		if (ammoBox->IsActive())
		{
			const X::Math::Circle ammoCircle = survivor->GetBoundingCircle();
			const X::Math::Circle survivorCircle = ammoBox->GetBoundingCircle();

			const float distance = X::Math::Distance(ammoCircle.center, survivorCircle.center);
			const float radii = ammoCircle.radius + survivorCircle.radius;

			if (distance <= radii)
			{
				// At this point, collision has been detected!
				ammoBox->Kill();
				break;
			}
		}
	}
}