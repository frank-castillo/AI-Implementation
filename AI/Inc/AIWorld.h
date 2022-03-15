#pragma once

#include "Entity.h"
#include "PartitionGrid.h"

namespace AI
{
	class AIWorld
	{
	public:
		using Obstacles = std::vector<X::Math::Circle>;
		using Walls = std::vector<X::Math::LineSegment>;

		void Initialize(float worldWidth, float worldHeight);
		void Update();

		void RegisterEntity(Entity* entity);
		void UnregisterEntity(Entity* entity);

		void AddObstacle(const X::Math::Circle& obstacle);
		void AddWall(const X::Math::LineSegment& wall);

		Entity* GetClosest(const X::Math::Vector2& position, uint32_t typeID) const;
		EntityPtrs GetEntitiesInRange(const X::Math::Circle& range, uint32_t typeID);

		bool HasLineOfSight(const X::Math::LineSegment& lineSegment) const;

		EntityPtrs GetEntities() const { return mEntities; }
		const auto& GetObstacles() const { return mObstacles; }
		const auto& GetWalls() const { return mWalls; }

		uint32_t GetNextID()const
		{
			XASSERT(mNextID < UINT32_MAX, "AIWorld -- Run out of IDs!");
			return mNextID++;
		}

	private:
		PartitionGrid<Entity> mPartitionGrid;
		EntityPtrs mEntities;

		Obstacles mObstacles;
		Walls mWalls;
		mutable uint32_t mNextID = 0;
	};
}

