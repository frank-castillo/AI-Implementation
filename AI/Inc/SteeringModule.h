#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class SteeringModule final
	{
	public:
		SteeringModule(Agent& agent);

		template <class NewBehaviourType>
		NewBehaviourType* AddBehaviour()
		{
			static_assert(std::is_base_of_v<SteeringBehaviour, NewBehaviourType>, "SteeringModule -- Can only add behaviours derived from SteeringBehaviour.");
			auto& newBehaviour = mBehaviours.emplace_back(std::make_unique<NewBehaviourType>());
			return static_cast<NewBehaviourType*>(newBehaviour.get());
		}

		X::Math::Vector2 Calculate();

	private:
		Agent& mAgent;
		std::vector<std::unique_ptr<SteeringBehaviour>> mBehaviours;
	};
}
