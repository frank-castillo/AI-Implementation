#pragma once

#include "State.h"

namespace AI
{
	template <class AgentType>
	class StateMachine
	{
	public:
		using StateType = State<AgentType>;

		StateMachine(AgentType& agent)
			:mAgent(agent)
		{

		}

		// Why is this not good?
		// -Implies someone else has to know what the state is going to be
		// -There is no need to have someone else create the memory and then take ownership
		/*void AddState(StateType* newState)
		{
			mStates.push_back(newState)
		}*/

		template<class NewStateType>
		void AddState(StateType* newState)
		{
			static_assert(std::is_base_of_v<StateType, NewStateType>, "StateMachine -- can only add state for AgentType");
			mStates.push_back(std::make_unique<NewStateType>());
		}

		void Update(float deltaTime)
		{
			XASSERT(mCurrentState != nullptr, "StateMachine -- current state isn null!");
			mCurrentState->Update(mAgent, deltaTime);
		}

		void ChangeState(int index)
		{
			XASSERT(index >= 0 && index < mStates.size(), "StateMachine -- Invalid index %i, state count = %zu", index, mStates.size());
			if (mCurrentState)
				mCurrentState->Exit(mAgent);
			mCurrentState = mStates[index].get();
			mCurrentState->Enter(mAgent);
		}

	private:
		AgentType& mAgent;
		StateType* mCurrentState = nullptr;
		std::vector<std::unique_ptr<StateType>> mStates;
	};
}
