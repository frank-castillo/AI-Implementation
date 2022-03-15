#include "Precompiled.h"

#include "AIWorld.h"

using namespace AI;

namespace
{
	constexpr float partitionGridSize = 100.0f;
}

void AIWorld::Initialize(float worldWidth, float worldHeight)
{
	const size_t columns = static_cast<size_t>(std::ceilf(worldWidth / partitionGridSize));
	const size_t rows = static_cast<size_t>(std::ceilf(worldHeight / partitionGridSize));
	mPartitionGrid.Resize(columns, rows);
}

void AIWorld::Update()
{
	mPartitionGrid.ClearCells();
	for (auto entity : mEntities)
	{
		const size_t column = static_cast<size_t>(entity->position.x / partitionGridSize);
		const size_t row = static_cast<size_t>(entity->position.y / partitionGridSize);
		mPartitionGrid.GetCell(column, row).push_back(entity);
	}
}

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

void AIWorld::AddObstacle(const X::Math::Circle& obstacle)
{
	mObstacles.push_back(obstacle);
}

void AIWorld::AddWall(const X::Math::LineSegment& wall)
{
	mWalls.push_back(wall);
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

EntityPtrs AI::AIWorld::GetEntitiesInRange(const X::Math::Circle& range, uint32_t typeID)
{
	int minX = static_cast<int>((range.center.x - range.radius) / partitionGridSize);
	int maxX = static_cast<int>((range.center.x + range.radius) / partitionGridSize);
	int minY = static_cast<int>((range.center.y - range.radius) / partitionGridSize);
	int maxY = static_cast<int>((range.center.y + range.radius) / partitionGridSize);

	minX = X::Math::Max(minX, 0);
	maxX = X::Math::Min(maxX, static_cast<int>(mPartitionGrid.GetColumns()) - 1);
	minY = X::Math::Max(minY, 0);
	maxY = X::Math::Min(maxY, static_cast<int>(mPartitionGrid.GetRows()) - 1);

	EntityPtrs entities;
	for (int y = minY; y <= maxY; ++y)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			auto& cell = mPartitionGrid.GetCell(x, y);
			for (auto& entity : cell)
			{
				if (entity->GetTypeID() == typeID)
					entities.push_back(entity);
			}
		}
	}

	return entities;
}

bool AIWorld::HasLineOfSight(const X::Math::LineSegment& lineSegment) const
{
	for (auto& wall : mWalls)
	{
		if (X::Math::Intersect(lineSegment, wall))
			return false;
	}
	for (auto& obstacle : mObstacles)
	{
		if (X::Math::Intersect(lineSegment, obstacle))
			return false;
	}
	return true;
}
