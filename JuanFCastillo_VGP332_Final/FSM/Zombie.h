#pragma once

#include <AI.h>
#include <XEngine.h>

class Zombie : public AI::Agent
{
public:
	enum State
	{
		Idle,
		Wander,
		Run,
	};

	Zombie(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ChangeState(State state);

	// Specific Member functions

private:
	std::unique_ptr<AI::StateMachine<Zombie>> mStateMachine;
	X::TextureId mTextureID = 0;
	//float mHunger;
};

