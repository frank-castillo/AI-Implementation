#include "Survivor.h"

#include "SurvivorStates.h"
#include "TypeIDs.h"

Survivor::Survivor(AI::AIWorld& world)
	: Agent(world, Types::SurvivorID)
{
}

void Survivor::Load()
{
	// Setup state machine
	mStateMachine = std::make_unique<AI::StateMachine<Survivor>>(*this);
	mStateMachine->AddState<SurvivorIdle>();
	mStateMachine->AddState<SurvivorWander>();
	mStateMachine->AddState<SurvivorRun>();
	mStateMachine->ChangeState(Idle);

	mTextureID = X::LoadTexture("survivor_handgun.png");
}

void Survivor::Unload()
{
	mTextureID = 0;
}

void Survivor::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Survivor::Render()
{
	X::DrawSprite(mTextureID, position);
}

void Survivor::ChangeState(State state)
{
	mStateMachine->ChangeState(state);
}
