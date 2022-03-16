#include "ZombieStates.h"

namespace
{
	const X::Math::Vector2 debugTextOffset(30.0f, -20.0f);
}

void ZombieIdle::Enter(Zombie& agent)
{
	mWaitTime = 1.0f;
}

void ZombieIdle::Update(Zombie& agent, float deltaTime)
{
	mWaitTime -= deltaTime;

	if (mWaitTime <= 0.0f)
	{
		agent.ChangeState(Zombie::Wander);
	}

	std::string str;
	str = "Idle";
	str += "\n";
	str += std::to_string(mWaitTime);
	str += "\n";
	X::DrawScreenText(str.c_str(), agent.position + debugTextOffset, 16.0f, X::Colors::White);
}

void ZombieIdle::Exit(Zombie& agent)
{
}

///////////////////////////////////////////////////////////////////////////////////

void ZombieWander::Enter(Zombie& agent)
{
	agent.destination = X::RandomVector2({ 100.0f, 100.0f }, { 1180.0f, 620.0f });
}

void ZombieWander::Update(Zombie& agent, float deltaTime)
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
		agent.ChangeState(Zombie::Idle);
	}

	X::DrawScreenDiamond(agent.destination, 20.0f, X::Colors::Green);
	X::DrawScreenText("Wander", agent.position + debugTextOffset, 16.0f, X::Colors::White);
}

void ZombieWander::Exit(Zombie& agent)
{
}
