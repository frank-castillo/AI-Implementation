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
