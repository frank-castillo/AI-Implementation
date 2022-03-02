#pragma once

#include <AI.h>
#include <XEngine.h>

class SCV : public AI::Agent
{
public:
	SCV(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ShowDebug(bool debug);

	void SetSeek(bool active) { mSeekBehaviour->SetActive(active); }
	void SetFlee(bool active) { mFleeBehaviour->SetActive(active); }
	void SetArrive(bool active) { mArriveBehaviour->SetActive(active); }
	void SetPursuit(bool active) { mPursuitBehaviour->SetActive(active); }
	void SetWander(bool active) { mWanderBehaviour->SetActive(active); }

private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	std::array<X::TextureId, 16> mTextureIDs;

	AI::SeekBehaviour* mSeekBehaviour = nullptr;
	AI::FleeBehaviour* mFleeBehaviour = nullptr;
	AI::ArriveBehaviour* mArriveBehaviour = nullptr;
	AI::PursuitBehaviour* mPursuitBehaviour = nullptr;
	AI::WanderBehaviour* mWanderBehaviour = nullptr;
};

