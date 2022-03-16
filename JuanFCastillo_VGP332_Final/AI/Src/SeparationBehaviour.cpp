#include "Precompiled.h"
#include "SeparationBehaviour.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 AI::SeparationBehaviour::Calculate(Agent& agent)
{
	X::Math::Vector2 separation;

	if (agent.neighbours.empty()) return X::Math::Vector2{};

	for (auto& neighbour : agent.neighbours)
	{
		X::Math::Vector2 vecAwayNeighbour = agent.position - neighbour->position;
		vecAwayNeighbour = X::Math::Normalize(vecAwayNeighbour);
		
		// Calculate distance from agent to its neighbour
		float distance = X::Math::Sqrt((agent.position.x - neighbour->position.x) * (agent.position.x - neighbour->position.x)
			+ (agent.position.y - neighbour->position.y) * (agent.position.y - neighbour->position.y));

		// How much the distance will affect the separation force
		vecAwayNeighbour /= distance;

		// Add speed to the force
		vecAwayNeighbour *= mMultiplier;

		// Store the force
		separation += vecAwayNeighbour;
	}

	const auto seekForce = separation - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + separation, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
	}

	return seekForce;
}

void AI::SeparationBehaviour::SetupMultiplier(float multiplier)
{
	mMultiplier = multiplier;
}