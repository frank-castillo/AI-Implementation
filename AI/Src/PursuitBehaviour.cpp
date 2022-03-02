#include "Precompiled.h"
#include "PursuitBehaviour.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 AI::PursuitBehaviour::Calculate(Agent& agent)
{
	agent.destination = mTarget->position + mTarget->velocity;

	const auto agentToTarget = mTarget->position - agent.position;
	const float distToDest = X::Math::Magnitude(agentToTarget) * 3.0f;
	if (distToDest <= 0.0f)
		return {};

	const auto desiredVelocity = (agentToTarget / distToDest) * agent.maxSpeed;
	const auto seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
	}

	return seekForce;
}
