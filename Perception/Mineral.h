#pragma once

#include <AI.h>
#include <XEngine.h>

class Mineral : public AI::Entity
{
public:
	Mineral(AI::AIWorld& world);

	void Initialize();

	void Render();

private:
	X::TextureId mTextureId;
};