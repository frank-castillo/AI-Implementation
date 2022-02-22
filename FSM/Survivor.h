#pragma once

#include <AI.h>
#include <XEngine.h>

class Survivor : public AI::Agent
{
public:
	enum State
	{
		Idle,
		Wander,
		Run,
	};

	Survivor(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ChangeState(State state);

	// Specific Member functions

private:
	std::unique_ptr<AI::StateMachine<Survivor>> mStateMachine;
	X::TextureId mTextureID = 0;
};

