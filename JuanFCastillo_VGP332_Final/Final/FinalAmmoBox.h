#pragma once

#include <AI.h>
#include <XEngine.h>

class AmmoBox : public AI::Entity
{
public:
	AmmoBox(AI::AIWorld& world);

	void Initialize();
	void Render();

	bool IsActive() const { return isActive; }

	void RandomizeLocation();
	void Kill();
	X::Math::Circle GetBoundingCircle() const { return X::Math::Circle(position, mHalfSpriteWidth); }

private:
	X::TextureId mTextureId;
	float mSpriteHeight;
	float mSpriteWidth;
	float mHalfSpriteWidth;
	bool isActive = false;
};

