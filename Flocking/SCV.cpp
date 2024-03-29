#include "SCV.h"

#include "TypeIDs.h"

/// <summary>
/// Extern 
/// </summary>
extern float wanderJitter;
extern float wanderRadius;
extern float wanderDistance;
extern float alignmentWeight;
extern float cohesionWeight;
extern float separationWeight;
extern float alignmentMultiplier;
extern float cohesionMultiplier;
extern float separationMultiplier;

SCV::SCV(AI::AIWorld& world)
	: Agent(world, Types::SCVID)
{
}

void SCV::Load()
{
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mAlignmentBehaviour = mSteeringModule->AddBehaviour<AI::AlignmentBehaviour>();
	mCohesionBehaviour = mSteeringModule->AddBehaviour<AI::CohesionBehaviour>();
	mSeparationBehaviour = mSteeringModule->AddBehaviour<AI::SeparationBehaviour>();
	mWanderBehaviour = mSteeringModule->AddBehaviour<AI::WanderBehaviour>();

	mAlignmentBehaviour->SetActive(true);
	mCohesionBehaviour->SetActive(true);
	mSeparationBehaviour->SetActive(true);
	mWanderBehaviour->SetActive(true);

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
	if (mWanderBehaviour->IsActive())
	{
		mWanderBehaviour->Setup(wanderRadius, wanderDistance, wanderJitter);
	}

	mAlignmentBehaviour->SetupMultiplier(alignmentMultiplier);
	mCohesionBehaviour->SetupMultiplier(cohesionMultiplier);
	mSeparationBehaviour->SetupMultiplier(separationMultiplier);

	mAlignmentBehaviour->SetWeight(alignmentWeight);
	mCohesionBehaviour->SetWeight(cohesionWeight);
	mSeparationBehaviour->SetWeight(separationWeight);

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
		position.y += screenHeight;
	if (position.y >= screenHeight)
		position.y -= screenHeight;

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
	mAlignmentBehaviour->ShowDebug(debug);
	mCohesionBehaviour->ShowDebug(debug);
	mSeparationBehaviour->ShowDebug(debug);
	mWanderBehaviour->ShowDebug(debug);
}
