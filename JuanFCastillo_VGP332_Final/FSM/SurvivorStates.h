#pragma once

#include "Survivor.h"
#include "Zombie.h"

class SurvivorIdle : public AI::State<Survivor>
{
public:
	void Enter(Survivor& agent) override;
	void Update(Survivor& agent, float deltaTime) override;
	void Exit(Survivor& agent) override;

private:
	float mWaitTime = 0.0f;
};

class SurvivorWander : public AI::State<Survivor>
{
public:
	void Enter(Survivor& agent) override;
	void Update(Survivor& agent, float deltaTime) override;
	void Exit(Survivor& agent) override;
};

class SurvivorRun : public AI::State<Survivor>
{
	void Enter(Survivor& agent) override;
	void Update(Survivor& agent, float deltaTime) override;
	void Exit(Survivor& agent) override;
private:
	Zombie* mClosestZombie;
};

