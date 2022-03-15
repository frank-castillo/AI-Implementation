#include "VisualSensor.h"

#include "TypeIds.h"

void VisualSensor::Update(AI::Agent& agent, AI::MemoryRecords& memory, float deltaTime)
{
	const auto& entities = agent.world.GetEntities();
	for (auto& entity : entities)
	{
		// Check if this is mineral
		const uint32_t typeId = entity->GetTypeID();
		if (typeId != TypeIds::Mineral)
			continue;

		// Check view distance
		X::Math::Vector2 posToTarget = entity->position - agent.position;
		if (X::Math::MagnitudeSqr(posToTarget) > X::Math::Sqr(viewRange))
			continue;

		// Check view angle
		X::Math::Vector2 dirToTarget = X::Math::Normalize(posToTarget);
		float dot = X::Math::Dot(agent.heading, dirToTarget);
		float angleToTarget = acos(dot);
		if (angleToTarget > viewHalfAngle)
			continue;

		// Check line of sight
		X::Math::LineSegment lineToTarget(agent.position, entity->position);
		if (!agent.world.HasLineOfSight(lineToTarget))
		{
			X::DrawScreenLine(agent.position, entity->position, X::Colors::Red);
			continue;
		}

		// Have I seen this before?
		auto iter = memory.begin();
		for (; iter != memory.end(); ++iter)
			if (iter->uniqueId == entity->GetUniqueID())
				break;

		if (iter != memory.end())
		{
			// If record already exists, just update record
			iter->properties["lastSeenPosition"] = entity->position;
			iter->lastRecordedTime = X::GetTime();
		}
		else
		{
			// Otherwise create a new record for this entity
			auto& newRecord = memory.emplace_back();
			newRecord.uniqueId = entity->GetUniqueID();
			newRecord.properties["lastSeenPosition"] = entity->position;
			newRecord.lastRecordedTime = X::GetTime();
		}
	}

	// Debug
	auto fovStart = X::Math::Rotate(agent.heading * viewRange, -viewHalfAngle);
	auto fovEnd = X::Math::Rotate(agent.heading * viewRange, viewHalfAngle);
	X::DrawScreenLine(agent.position, agent.position + fovStart, X::Colors::Cyan);
	X::DrawScreenLine(agent.position, agent.position + fovEnd, X::Colors::Cyan);

	auto angle = atan2(agent.heading.y, agent.heading.x);
	X::DrawScreenArc(agent.position, viewRange, angle - viewHalfAngle, angle + viewHalfAngle, X::Colors::LightCyan);
}