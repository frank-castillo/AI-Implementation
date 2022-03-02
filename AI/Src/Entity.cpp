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

X::Math::Matrix3 Entity::GetWorldTransform() const
{
	const auto h = heading;
	const auto s = X::Math::PerpendicularRH(h);
	const auto d = position;

	return{
		s.x, s.y, 0.0f,
		h.x, h.y, 0.0f,
		d.x, d.y, 1.0f
	};
}
