#pragma once

#include "Entity.h"

namespace AI
{
	class AIWorld
	{
	public:
		uint32_t GetNextID()const
		{
			XASSERT(mNextID < UINT32_MAX, "AIWorld -- Run out of IDs!");
			return mNextID++;
		}

		void RegisterEntity(Entity* entity);
		void UnregisterEntity(Entity* entity);

		Entity* GetClosest(const X::Math::Vector2& position, uint32_t typeID) const;

	private:
		EntityPtrs mEntities;
		mutable uint32_t mNextID = 0;
	};
}

