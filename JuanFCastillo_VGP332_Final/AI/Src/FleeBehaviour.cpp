#include "Precompiled.h"
#include "FleeBehaviour.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 AI::FleeBehaviour::Calculate(Agent& agent)
{
	const auto agentToDest = agent.destination - agent.position;
	const float distToDest = X::Math::Magnitude(agentToDest);
	if (distToDest > panicDistance)
		return {};

	const auto desiredVelocity = -(agentToDest / distToDest) * agent.maxSpeed;
	const auto fleeForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
	}

	return fleeForce;
}