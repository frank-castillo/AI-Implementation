#include "Zombie.h"

#include "ZombieStates.h"
#include "TypeIDs.h"

Zombie::Zombie(AI::AIWorld& world)
	:Agent(world, Types::ZombieID)
{
}

void Zombie::Load()
{
	mStateMachine = std::make_unique<AI::StateMachine<Zombie>>(*this);
	mStateMachine->AddState<ZombieIdle>();
	mStateMachine->AddState<ZombieWander>();
	mStateMachine->ChangeState(Idle);

	mTextureID = X::LoadTexture("zombie_idle.png");
}

void Zombie::Unload()
{
	mTextureID = 0;
}

void Zombie::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}

void Zombie::Render()
{
	X::DrawSprite(mTextureID, position);
}

void Zombie::ChangeState(State state)
{
	mStateMachine->ChangeState(state);
}
