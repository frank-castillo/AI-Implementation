#pragma once

#include <XEngine.h>

namespace AI
{
	class Agent;

	class SteeringBehaviour
	{
	public:
		virtual ~SteeringBehaviour() = default;

		virtual X::Math::Vector2 Calculate(Agent& agent) = 0;

		void SetActive(bool active) { mActive = active; }
		bool IsActive() const { return mActive; }

		void ShowDebug(bool debug) { mDebug = debug; }
		bool IsDebug() const { return mDebug; }

	private:
		bool mActive = false;
		bool mDebug = false;
	};
}