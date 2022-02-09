#include "Precompiled.h"
#include "Entity.h"

#include "AIWorld.h"

using namespace AI;

AI::Entity::Entity(AIWorld& world, uint32_t typeID)
	: world(world),
	mUniqueID(static_cast<uint64_t>(typeID) << 32 | world.GetNextID())
{
	world.RegisterEntity(this); // Registers when born
}

AI::Entity::~Entity()
{
	world.UnregisterEntity(this); // Unregisters when dead
}
