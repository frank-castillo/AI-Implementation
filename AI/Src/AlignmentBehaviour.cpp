#include "Precompiled.h"
#include "AlignmentBehaviour.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 AI::AlignmentBehaviour::Calculate(Agent& agent)
{
	X::Math::Vector2 alignment = agent.heading;

	if (agent.neighbours.empty()) return X::Math::Vector2{};

	for (auto& neighbour : agent.neighbours)
	{
		// Add all the heads into one
		alignment += neighbour->heading;
	}

	// Divide by all agents in our neighbourhood
	/*alignment /= agent.neighbours.size() + 1;
	alignment -= agent.heading;
	alignment *= mMultiplier;
	const auto seekForce = alignment - agent.velocity;*/

	alignment = X::Math::Normalize(alignment);
	const auto desiredVelocity = alignment * agent.maxSpeed;
	const auto seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + alignment, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
	}

	return seekForce;
}

void AI::AlignmentBehaviour::SetupMultiplier(float multiplier)
{
	mMultiplier = multiplier;
}