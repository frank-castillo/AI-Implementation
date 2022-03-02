#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class FleeBehaviour : public SteeringBehaviour
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;

		void SetPanicDistance(float distance) { panicDistance = distance; }

	private:
		float panicDistance = 100.0f;
	};
}
