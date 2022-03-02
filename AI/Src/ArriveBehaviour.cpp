#include "Precompiled.h"
#include "ArriveBehaviour.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 AI::ArriveBehaviour::Calculate(Agent& agent)
{
	const auto agentToDest = agent.destination - agent.position;
	const float distToDest = X::Math::Magnitude(agentToDest);
	if (distToDest <= 0.0f)
		return {};

	auto desiredVelocity = (agentToDest / distToDest) * agent.maxSpeed;
	
	/*if (distToDest < mSlowingDistance)
	{
		desiredVelocity = desiredVelocity * (distToDest / mSlowingDistance) * 0.1f;
	}*/

	if (distToDest < mSlowingDistance)
	{
		desiredVelocity = desiredVelocity * (distToDest / mSlowingDistance);
	}
	else
	{
		desiredVelocity = desiredVelocity;
	}

	const auto seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
	}

	return seekForce;
}
