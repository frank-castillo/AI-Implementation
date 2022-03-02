#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class ArriveBehaviour : public SteeringBehaviour
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;

		void SetSlowingDistance(float distance) { mSlowingDistance = distance; }

	private:
		float mSlowingDistance = 250.0f;
	};
}