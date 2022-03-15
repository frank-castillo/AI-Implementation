#include "Precompiled.h"
#include "CohesionBehaviour.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 AI::CohesionBehaviour::Calculate(Agent& agent)
{
	X::Math::Vector2 centerOfMass;
	if (agent.neighbours.empty()) return X::Math::Vector2{};

	for (auto& neighbour : agent.neighbours)
	{
		centerOfMass += neighbour->position;
	}
	centerOfMass /= agent.neighbours.size();

	// Compute agent to move towards center of gravity
	const auto agentToDest = centerOfMass - agent.position;
	const float distToDest = X::Math::Magnitude(agentToDest);
	if (distToDest <= 0) return{};

	const auto desiredVelocity = agentToDest / distToDest * mMultiplier;
	const auto cohesionSeekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
	}

	return cohesionSeekForce;
}

void AI::CohesionBehaviour::SetupMultiplier(float multiplier)
{
	mMultiplier = multiplier;
}