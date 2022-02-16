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


	private:
		EntityPtrs mEntities;
		mutable uint32_t mNextID = 0;
	};
}

