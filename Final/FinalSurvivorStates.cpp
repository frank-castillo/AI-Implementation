#include "FinalSurvivorStates.h"
#include "IDTypesFinal.h"

void SurvivorWander::Enter(Survivor& agent)
{
	agent.SetWander(true);
}

void SurvivorWander::Update(Survivor& agent, float deltaTime)
{
	const auto& memoryBanks = agent.GetMemoryRecords();
	const AI::Entity* closestZombie = agent.world.GetClosest(agent.position, EntityTypes::ZombieType);
	const auto distanceToZombie = closestZombie->position - agent.position;
	const float zombieDistance = X::Math::Magnitude(distanceToZombie);
	X::DrawScreenDiamond(closestZombie->position, 20.0f, X::Colors::Red);

	// If the closest zombie close enough
	if (closestZombie != nullptr && zombieDistance < 150) // add distance check
	{
		agent.target = closestZombie;
		agent.ChangeState(Survivor::Run);
	}
	else if(!memoryBanks.empty())
	{
		// Transition
		agent.ChangeState(Survivor::GetAmmo);
	}
}

void SurvivorWander::Exit(Survivor& agent)
{
}

///////////////////////////////////////////////////////////////////////////

void SurvivorGetAmmo::Enter(Survivor& agent)
{
}

void SurvivorGetAmmo::Update(Survivor& agent, float deltaTime)
{
}

void SurvivorGetAmmo::Exit(Survivor& agent)
{
}

///////////////////////////////////////////////////////////////////////////

void SurvivorRun::Enter(Survivor& agent)
{
	agent.SetWander(false);
	agent.SetFlee(true);
}

void SurvivorRun::Update(Survivor& agent, float deltaTime)
{
}

void SurvivorRun::Exit(Survivor& agent)
{
}
