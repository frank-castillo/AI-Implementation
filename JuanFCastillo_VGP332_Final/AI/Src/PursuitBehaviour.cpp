#include "Precompiled.h"
#include "PursuitBehaviour.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 AI::PursuitBehaviour::Calculate(Agent& agent)
{
	// Obtain data from target we are going to chase
	const auto& target = agent.target;

	// Direction from agent to target
	const auto agentToTarget = target->position - agent.position;
	const float distance = X::Math::Magnitude(agentToTarget);

	if (distance > chaseDistance)
	{
		agent.destination = target->position + target->velocity;
	}
	else
	{
		agent.destination = target->position;
	}

	const auto agentToDest = agent.destination - agent.position;
	const float distToDest = X::Math::Magnitude(agentToTarget);
	if (distToDest <= 0.0f)
		return {};

	const auto desiredVelocity = (agentToDest / distToDest) * agent.maxSpeed;
	const auto seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
	}

	return seekForce;
}
