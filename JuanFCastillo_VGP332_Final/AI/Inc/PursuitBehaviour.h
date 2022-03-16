#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class PursuitBehaviour : public SteeringBehaviour
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	private:
		const float chaseDistance = 200.0f;
	};
}