#include "FinalSurvivorStates.h"
#include "IDTypesFinal.h"
#include "FinalZombie.h"
#include "FinalAmmoBox.h"

void SurvivorWander::Enter(Survivor& agent)
{
	agent.SetWander(true);
}

void SurvivorWander::Update(Survivor& agent, float deltaTime)
{
	const auto& memoryBanks = agent.GetMemoryRecords();

	const AI::Agent* closestZombie = static_cast<Zombie*>(agent.world.GetClosest(agent.position, EntityTypes::ZombieType));
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
	agent.SetWander(false);
}

///////////////////////////////////////////////////////////////////////////

void SurvivorGetAmmo::Enter(Survivor& agent)
{
	agent.SetArrive(true);

	const auto& memoryRecords = agent.GetMemoryRecords();
	if (memoryRecords.empty() == false)
	{
		const auto& memoryFront = memoryRecords.front();
		for (auto& entity : agent.world.GetEntities())
		{
			if (entity->GetUniqueID() == memoryFront.uniqueId)
			{
				agent.destination = entity->position;
			}
		}
	}
}

void SurvivorGetAmmo::Update(Survivor& agent, float deltaTime)
{
}

void SurvivorGetAmmo::Exit(Survivor& agent)
{
	agent.SetArrive(false);
}

///////////////////////////////////////////////////////////////////////////

void SurvivorRun::Enter(Survivor& agent)
{
	agent.SetFlee(true);
}

void SurvivorRun::Update(Survivor& agent, float deltaTime)
{
}

void SurvivorRun::Exit(Survivor& agent)
{
}
