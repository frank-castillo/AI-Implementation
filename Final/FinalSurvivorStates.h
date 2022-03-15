#pragma once
#include "FinalSurvivor.h"

class SurvivorWander : public AI::State<Survivor>
{
public:
	void Enter(Survivor& agent) override;
	void Update(Survivor& agent, float deltaTime) override;
	void Exit(Survivor& agent) override;
};

class SurvivorRun : public AI::State<Survivor>
{
public:
	void Enter(Survivor& agent) override;
	void Update(Survivor& agent, float deltaTime) override;
	void Exit(Survivor& agent) override;
};

class SurvivorGetAmmo : public AI::State<Survivor>
{
public:
	void Enter(Survivor& agent) override;
	void Update(Survivor& agent, float deltaTime) override;
	void Exit(Survivor& agent) override;
};

