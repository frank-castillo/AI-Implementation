#include "FinalSurvivorStates.h"
#include "IDTypesFinal.h"
#include "FinalZombie.h"
#include "FinalAmmoBox.h"

void SurvivorWander::Enter(Survivor& agent)
{
	agent.SetCurrentStateName("Wander");
	agent.SetWander(true);
}

void SurvivorWander::Update(Survivor& agent, float deltaTime)
{
	agent.GetPerceptionModule()->Update(deltaTime);

	const AI::Agent* closestZombie = static_cast<Zombie*>(agent.world.GetClosest(agent.position, EntityTypes::ZombieType));
	const auto distanceToZombie = closestZombie->position - agent.position;
	const float zombieDistance = X::Math::Magnitude(distanceToZombie);
	X::DrawScreenDiamond(closestZombie->position, 20.0f, X::Colors::Red);

	const auto& memoryBanks = agent.GetMemoryRecords();

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
	agent.SetCurrentStateName("GetAmmo");
	agent.SetArrive(true);

	agent.maxSpeed = 300.0f;

	const auto& memoryRecords = agent.GetMemoryRecords();
	if (memoryRecords.empty() == false)
	{
		const auto& memoryFront = memoryRecords.front();
		for (auto& entity : agent.world.GetEntities())
		{
			if (entity->GetUniqueID() == memoryFront.uniqueId)
			{
				agent.destination = entity->position;
				const int dummy = 2;
			}
		}
	}
}

void SurvivorGetAmmo::Update(Survivor& agent, float deltaTime)
{
	agent.GetPerceptionModule()->Update(deltaTime);

	const AI::Agent* closestZombie = static_cast<Zombie*>(agent.world.GetClosest(agent.position, EntityTypes::ZombieType));
	const auto distanceToZombie = closestZombie->position - agent.position;
	const float zombieDistance = X::Math::Magnitude(distanceToZombie);
	X::DrawScreenDiamond(closestZombie->position, 20.0f, X::Colors::Red);

	const auto& memoryRecords = agent.GetMemoryRecords();

	// If the closest zombie close enough
	if (closestZombie != nullptr && zombieDistance < 150) // add distance check
	{
		agent.target = closestZombie;
		//agent.ChangeState(Survivor::Run);
	}
	else if (memoryRecords.empty())
	{
		// Transition
		agent.ChangeState(Survivor::Wander);
	}
}

void SurvivorGetAmmo::Exit(Survivor& agent)
{
	agent.SetArrive(false);
}

///////////////////////////////////////////////////////////////////////////

void SurvivorRun::Enter(Survivor& agent)
{
	agent.SetCurrentStateName("Run");
	agent.SetFlee(true);
}

void SurvivorRun::Update(Survivor& agent, float deltaTime)
{
	const AI::Agent* closestZombie = static_cast<Zombie*>(agent.world.GetClosest(agent.position, EntityTypes::ZombieType));
	const auto distanceToZombie = closestZombie->position - agent.position;
	const float zombieDistance = X::Math::Magnitude(distanceToZombie);
	X::DrawScreenDiamond(closestZombie->position, 20.0f, X::Colors::Red);
	agent.destination = closestZombie->position;

	// If the closest zombie close enough
	if (closestZombie != nullptr && zombieDistance > 150) // add distance check
	{
		agent.target = nullptr;
		agent.ChangeState(Survivor::Wander);
	}
}

void SurvivorRun::Exit(Survivor& agent)
{
	agent.SetFlee(false);
}
