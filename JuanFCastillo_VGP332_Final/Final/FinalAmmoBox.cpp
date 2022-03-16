#include "FinalAmmoBox.h"

#include "IDTypesFinal.h"

AmmoBox::AmmoBox(AI::AIWorld& world)
	:Entity(world, EntityTypes::AmmoType)
{
}

void AmmoBox::Initialize()
{
	mTextureId = X::LoadTexture("bullet2.png");

	mSpriteWidth = static_cast<float>(X::GetSpriteWidth(mTextureId));
	mSpriteHeight = static_cast<float>(X::GetSpriteHeight(mTextureId));

	mHalfSpriteWidth = mSpriteWidth / 2.0f;

	position = X::Math::Vector2{ FLT_MAX,FLT_MAX };
}

void AmmoBox::Render()
{
	if (isActive)
	{
		X::DrawSprite(mTextureId, position);
		X::DrawScreenCircle(GetBoundingCircle(), X::Colors::Red);
	}
}

void AmmoBox::Kill()
{
	isActive = false;
	position = X::Math::Vector2{FLT_MAX,FLT_MAX};
}

void AmmoBox::RandomizeLocation()
{
	isActive = true;
	position = X::Math::Vector2{};
	position = X::RandomVector2({ 500.0f, 100.0f }, { 780.0f, 710.0f });
	position.x += X::Random(0, 1) == 0 ? -300.0f : 300.0f;
}
