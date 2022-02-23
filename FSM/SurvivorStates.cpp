#include "SurvivorStates.h"

#include "TypeIDs.h"

namespace
{
	const X::Math::Vector2 debugTextOffset(30.0f, -20.0f);
	const float runSpeed = 200.0f;
}

void SurvivorIdle::Enter(Survivor& agent)
{
	mWaitTime = 1.0f;
}

void SurvivorIdle::Update(Survivor& agent, float deltaTime)
{
	// Task
	mWaitTime -= deltaTime;

	AI::Entity* closestZombie = agent.world.GetClosest(agent.position, Types::ZombieID);
	const auto distanceToZombie = closestZombie->position - agent.position;
	const float distance = X::Math::Magnitude(distanceToZombie);
	X::DrawScreenDiamond(closestZombie->position, 20.0f, X::Colors::Red);

	// If the closest zombie close enough
	if (closestZombie != nullptr && distance < 150) // add distance check
	{
		agent.ChangeState(Survivor::Run);
	}
	else if (mWaitTime <= 0) // Transition
	{
		agent.ChangeState(Survivor::Wander);
	}

	std::string str;
	str = "Idle";
	str += "\n";
	str += std::to_string(mWaitTime);
	str += "\n";
	str += "Distance to Zombie";
	str += "\n";
	str += std::to_string(distance);
	X::DrawScreenText(str.c_str(), agent.position + debugTextOffset, 16.0f, X::Colors::White);
}

void SurvivorIdle::Exit(Survivor& agent)
{
}

///////////////////////////////////////////////////////////////////////////

void SurvivorWander::Enter(Survivor& agent)
{
	agent.destination = X::RandomVector2({ 100.0f, 100.0f }, { 1180.0f, 620.0f });
}

void SurvivorWander::Update(Survivor& agent, float deltaTime)
{
	const auto agentToDest = agent.destination - agent.position;
	const float distance = X::Math::Magnitude(agentToDest);

	AI::Entity* closestZombie = agent.world.GetClosest(agent.position, Types::ZombieID);
	const auto distanceToZombie = closestZombie->position - agent.position;
	const float zombieDistance = X::Math::Magnitude(distanceToZombie);
	X::DrawScreenDiamond(closestZombie->position, 20.0f, X::Colors::Red);

	// If the closest zombie close enough
	if (closestZombie != nullptr && zombieDistance < 150) // add distance check
	{
		agent.ChangeState(Survivor::Run);
	}
	else if (distance > 10.0f)
	{
		// Task
		const auto direction = agentToDest / distance;
		agent.velocity = direction * 120.0f;
		agent.position += agent.velocity * deltaTime;
	}
	else
	{
		// Transition
		agent.ChangeState(Survivor::Idle);
	}

	X::DrawScreenDiamond(agent.destination, 20.0f, X::Colors::Cyan);
	X::DrawScreenText("Wander", agent.position + debugTextOffset, 16.0f, X::Colors::White);
}

void SurvivorWander::Exit(Survivor& agent)
{
}

///////////////////////////////////////////////////////////////////////////

void SurvivorRun::Enter(Survivor& agent)
{
	AI::Entity* closestZombie = agent.world.GetClosest(agent.position, Types::ZombieID);
	if (closestZombie != nullptr)
	{
		mClosestZombie = static_cast<Zombie*>(closestZombie);
		agent.destination = closestZombie->position;
	}
	else
	{
		closestZombie = nullptr;
	}
}

void SurvivorRun::Update(Survivor& agent, float deltaTime)
{
	const auto agentToDest = agent.destination - agent.position;
	const float distance = X::Math::Magnitude(agentToDest);

	if (distance < 300.0f)
	{
		// Task
		auto direction = agentToDest / distance;
		direction *= -1;
		agent.velocity = direction * runSpeed;
		agent.position += agent.velocity * deltaTime;
	}
	else
	{
		// Transition
		agent.ChangeState(Survivor::Idle);
	}

	X::DrawScreenDiamond(agent.destination, 20.0f, X::Colors::Cyan);
	X::DrawScreenText("Eat", agent.position + debugTextOffset, 16.0f, X::Colors::Yellow);
}

void SurvivorRun::Exit(Survivor& agent)
{
}
