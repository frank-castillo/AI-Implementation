#include "Precompiled.h"
#include "WanderBehaviour.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 WanderBehaviour::Calculate(Agent& agent)
{
	// Apply random jitter to wander target
	auto newWanderTarget = mLocalWanderTarget + (X::RandomUnitCircle() * mWanderJitter);

	// Snap the new position back onto the wander circle
	newWanderTarget = X::Math::Normalize(newWanderTarget) * mWanderRadius;
	mLocalWanderTarget = newWanderTarget;

	// Project the new position forward in front of the agent
	newWanderTarget += X::Math::Vector2(0.0f, mWanderDistance);

	// Transform target into world space
	const auto worldTransform = agent.GetWorldTransform();
	const auto worldWanderTarget = X::Math::TransformCoord(newWanderTarget, worldTransform);

	// Check if we are already there
	const auto agentToDest = worldWanderTarget - agent.position;
	const float distToDest = X::Math::Magnitude(agentToDest);
	if (distToDest <= 0.0f)
		return {};

	// Seek to wander target
	const auto desiredVelocity = (agentToDest / distToDest) * agent.maxSpeed;
	const auto seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		const auto wanderCenter = X::Math::TransformCoord({ 0.0f, mWanderDistance }, worldTransform);
		X::DrawScreenCircle(wanderCenter, mWanderRadius, X::Colors::Green);
		X::DrawScreenDiamond(worldWanderTarget, 3.0f, X::Colors::Red);
		X::DrawScreenLine(agent.position, worldWanderTarget, X::Colors::Yellow);
	}

	return seekForce;
}

void WanderBehaviour::Setup(float radius, float distance, float jitter)
{
	mWanderRadius = radius;
	mWanderDistance = distance;
	mWanderJitter = jitter;
}
