#include "SurvivorStates.h"

#include "TypeIDs.h"

namespace
{
	const X::Math::Vector2 debugTextOffset(30.0f, -20.0f);
	const float runSpeed = 150.0f;
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
	if (closestZombie != nullptr)
	{
		//agent.ChangeState(Survivor::Run);
	}

	// Transition
	if (mWaitTime <= 0)
	{
		agent.ChangeState(Survivor::Wander);
	}

	std::string str;
	str = "Idle";
	str += "\n";
	str += std::to_string(mWaitTime);
	str += "\n";
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

	if (distance > 10.0f)
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
		agent.destination = -closestZombie->position;
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

	if (distance < 10.0f)
	{
		// Task
		const auto direction = agentToDest / distance;
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
