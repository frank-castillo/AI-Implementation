#pragma once

#include <AI.h>
#include <XEngine.h>

#include "FinalVisualSensor.h"

class Survivor : public AI::Agent
{
public:
	enum State
	{
		Wander,
		Run,
		GetAmmo
	};

	Survivor(AI::AIWorld& world);

	void Load();

	void Update(float deltaTime);
	void Render();

	void ChangeState(State state);

	void SetSeek(bool active) { mSeekBehaviour->SetActive(active); }
	void SetFlee(bool active) { mFleeBehaviour->SetActive(active); }
	void SetArrive(bool active) { mArriveBehaviour->SetActive(active); }
	void SetPursuit(bool active) { mPursuitBehaviour->SetActive(active); }
	void SetWander(bool active) { mWanderBehaviour->SetActive(active); }

	const auto& GetMemoryRecords() { return mPerceptionModule->GetMemoryRecords(); }
	const auto& GetPerceptionModule() { return mPerceptionModule; }
	void DeleteMemory() { mPerceptionModule->PopMemory(); }

	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(position - X::Math::Vector2{-20.0f, 5.0f}, mHalfSpriteWidth - 30.0f); }
	void SetDebug(bool active);

	void SetCurrentStateName(const char* str) { mCurrentStateName = str; }

private:
	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
	VisualSensor* mVisualSensor = nullptr;

	std::unique_ptr<AI::StateMachine<Survivor>> mStateMachine;

	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::SeekBehaviour* mSeekBehaviour = nullptr;
	AI::FleeBehaviour* mFleeBehaviour = nullptr;
	AI::ArriveBehaviour* mArriveBehaviour = nullptr;
	AI::PursuitBehaviour* mPursuitBehaviour = nullptr;
	AI::WanderBehaviour* mWanderBehaviour = nullptr;

	X::TextureId mTextureId = 0;
	float mSpriteHeight;
	float mSpriteWidth;
	float mHalfSpriteWidth;

	std::string mCurrentStateName;
};

