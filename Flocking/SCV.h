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

	void SetAlignment(bool active) { mAlignmentBehaviour->SetActive(active); }
	void SetCohesion(bool active) { mCohesionBehaviour->SetActive(active); }
	void SetSeparation(bool active) { mSeparationBehaviour->SetActive(active); }
	void SetWander(bool active) { mWanderBehaviour->SetActive(active); }

private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	std::array<X::TextureId, 16> mTextureIDs;

	AI::AlignmentBehaviour* mAlignmentBehaviour = nullptr;
	AI::CohesionBehaviour* mCohesionBehaviour = nullptr;
	AI::SeparationBehaviour* mSeparationBehaviour = nullptr;
	AI::WanderBehaviour* mWanderBehaviour = nullptr;
};

