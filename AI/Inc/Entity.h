#pragma once

namespace AI
{
	class AIWorld;

	class Entity
	{
	public:
		AIWorld& world;
		X::Math::Vector2 position = X::Math::Vector2::Zero();
		X::Math::Vector2 heading = X::Math::Vector2::YAxis();
		float radius = 1.0f;

	private:
		uint64_t mUniqueID = 0;
	};
}

// To fix circular inclusion, you have to ask yourself
// Does one file really needs to know about everything the other file?
// A way to fix that, is just using includes in the .cpp file
// Another way to fix this is using forward declaration
// class AIWorld;
// AIWorld& world;
// This way the compiler understands that you are asking for a class
// With this, code can compile and won't cause redundant calls to headers
