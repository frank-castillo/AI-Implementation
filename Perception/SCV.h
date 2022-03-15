#pragma once

#include "VisualSensor.h"
#include <AI.h>
#include <XEngine.h>

class SCV : public AI::Agent
{
public:
	SCV(AI::AIWorld& world);

	void Initialize();

	void Update(float deltaTime);
	void Render();

	void SetDebug(bool debug);

	void SetSeek(bool active) { mSeekBehavior->SetActive(active); }
	void SetWander(bool active) { mWanderBehavior->SetActive(active); }

private:
	// Perception stuff
	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
	VisualSensor* mVisualSensor = nullptr;

	// Steering stuff
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::SeekBehaviour* mSeekBehavior = nullptr;
	AI::WanderBehaviour* mWanderBehavior = nullptr;

	// Graphics stuff
	std::array<X::TextureId, 16> mTextureIds;
};