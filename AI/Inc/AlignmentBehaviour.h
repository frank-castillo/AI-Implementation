#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class AlignmentBehaviour : public SteeringBehaviour
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;

		void SetupMultiplier(float multiplier);

	private:
		float mMultiplier;
	};
}