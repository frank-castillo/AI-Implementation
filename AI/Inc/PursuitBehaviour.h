#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class PursuitBehaviour : public SteeringBehaviour
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
		void SetTarget(const Agent* agent) { mTarget = agent; }

	private:
		const Agent* mTarget;
	};
}