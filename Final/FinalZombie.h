#pragma once

#include <AI.h>
#include <XEngine.h>

class Zombie : public AI::Agent
{
public:
	Zombie(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ShowDebug(bool debug);
	void SetWander(bool active) { mWanderBehaviour->SetActive(active); }

private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::WanderBehaviour* mWanderBehaviour = nullptr;

	X::TextureId mTextureID = 0;
};

