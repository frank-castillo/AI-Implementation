#pragma once

namespace AI
{
	class AIWorld;
	class Entity;

	using EntityPtrs = std::vector<Entity*>;

	class Entity
	{
	public:
		// This are all Special Member functions
		Entity(AIWorld& world, uint32_t typeID);
		virtual ~Entity();

		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator=(Entity&) = delete;
		/// <summary>
		/// Special member functions are functions that could be created by the compiler
		/// if certain conditions are met!
		/// delete tells the compiler to not create those functions and limit
		/// our creation and destruction of Entities
		/// </summary>

		AIWorld& world; // This can only be initialized, not assigned!
		X::Math::Vector2 position = X::Math::Vector2::Zero();
		X::Math::Vector2 heading = X::Math::Vector2::YAxis();
		float radius = 1.0f;

		X::Math::Matrix3 GetWorldTransform() const;

		uint32_t GetTypeID() const { return static_cast<uint32_t>(mUniqueID >> 32); }
		uint64_t GetUniqueID() const { return mUniqueID; }

	private:
		const uint64_t mUniqueID = 0; // Only constructor sets it
	};
}

// If you do not have an AIWorld, you can't create an Entity

// To fix circular inclusion, you have to ask yourself
// Does one file really needs to know about everything the other file?
// A way to fix that, is just using includes in the .cpp file
// Another way to fix this is using forward declaration
// class AIWorld;
// AIWorld& world;
// This way the compiler understands that you are asking for a class
// With this, code can compile and won't cause redundant calls to headers
