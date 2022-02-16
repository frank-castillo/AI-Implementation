#include "Precompiled.h"

#include "AIWorld.h"

using namespace AI;

void AI::AIWorld::RegisterEntity(Entity* entity)
{
	XASSERT(std::find(mEntities.begin(), mEntities.end(), entity) == mEntities.end(),
		"AIWorld -- Entity already registered!");
	mEntities.push_back(entity);
}

void AI::AIWorld::UnregisterEntity(Entity* entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter != mEntities.end())
	{
		// Constant time removal
		std::iter_swap(iter, mEntities.end() - 1); 
		mEntities.pop_back();
	}
}

Entity* AIWorld::GetClosest(const X::Math::Vector2& position, uint32_t typeID) const
{
	Entity* closestEntity = nullptr;
	float closestDistanceSqr = FLT_MAX;

	for (auto entity : mEntities)
	{
		if (entity->GetTypeID() == typeID)
		{
			const float distSqr = X::Math::DistanceSqr(position, entity->position);
			if (distSqr < closestDistanceSqr)
			{
				closestEntity = entity;
				closestDistanceSqr = distSqr;
			}
		}
	}

	return closestEntity;
}

