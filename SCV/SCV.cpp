#include "SCV.h"

#include "TypeIDs.h"

SCV::SCV(AI::AIWorld& world)
	: Agent(world, Types::SCVID)
{
}

void SCV::Load()
{
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehaviour = mSteeringModule->AddBehaviour<AI::SeekBehaviour>();
	mFleeBehaviour = mSteeringModule->AddBehaviour<AI::FleeBehaviour>(); 
	mArriveBehaviour = mSteeringModule->AddBehaviour<AI::ArriveBehaviour>(); 
	mPursuitBehaviour = mSteeringModule->AddBehaviour<AI::PursuitBehaviour>(); 

	mSeekBehaviour->SetActive(true);
	mFleeBehaviour->SetActive(false);
	mFleeBehaviour->SetPanicDistance(100.f);
	mArriveBehaviour->SetActive(false);
	mPursuitBehaviour->SetActive(false);

	maxSpeed = 250.0f;

	for (int i = 0; i < mTextureIDs.size(); ++i)
	{
		char name[128];
		sprintf_s(name, "scv_%02i.png", i + 1);
		mTextureIDs[i] = X::LoadTexture(name);
	}
}

void SCV::Unload()
{
}

void SCV::Update(float deltaTime)
{
	const auto force = mSteeringModule->Calculate();

	const auto acceleration = force / mass;
	velocity += acceleration * deltaTime;

	// Make sure we don't exceed max speed
	if (X::Math::MagnitudeSqr(velocity) > X::Math::Sqr(maxSpeed))
		velocity = X::Math::Normalize(velocity) * maxSpeed;

	position += velocity * deltaTime;

	// Update heading if we have movement
	if (X::Math::MagnitudeSqr(velocity) > 1.0f)
		heading = X::Math::Normalize(velocity);

	// Screen wrapping
	const auto screenWidth = X::GetScreenWidth();
	const auto screenHeight = X::GetScreenHeight();
	if (position.x < 0.0f)
		position.x += screenWidth;
	if (position.x >= screenWidth)
		position.x -= screenWidth;
	if (position.y < 0.0f)
		position.y -= screenHeight;
	if (position.y >= screenHeight)
		position.y += screenHeight;

	// Show destination
	X::DrawScreenCircle(destination, 5.0f, X::Colors::Red);
}

void SCV::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	const float percent = angle / X::Math::kTwoPi;
	const int frame = static_cast<int>(percent * mTextureIDs.size()) % mTextureIDs.size();
	X::DrawSprite(mTextureIDs[frame], position);
}

void SCV::ShowDebug(bool debug)
{
	mSeekBehaviour->ShowDebug(debug);
	mFleeBehaviour->ShowDebug(debug);
	mArriveBehaviour->ShowDebug(debug);
	mPursuitBehaviour->ShowDebug(debug);
}
