#include "SCV.h"

#include "TypeIds.h"

extern float viewRange;
extern float viewAngle;

extern float wanderJitter;
extern float wanderRadius;
extern float wanderDistance;

namespace
{
	float ComputeImportance(const AI::Agent& agent, const AI::MemoryRecord& record)
	{
		float distance = X::Math::Distance(agent.position, record.GetProperty<X::Math::Vector2>("lastSeenPosition"));
		float distanceScore = 10000.0f - distance;
		return distanceScore;
	}
}

SCV::SCV(AI::AIWorld& world)
	: AI::Agent(world, TypeIds::SCV)
{
}

void SCV::Initialize()
{
	// Set agent attributes
	maxSpeed = 200.0f;

	// Perception
	mPerceptionModule = std::make_unique<AI::PerceptionModule>(*this, ComputeImportance);
	mVisualSensor = mPerceptionModule->AddSensor<VisualSensor>();

	// Steering
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehavior = mSteeringModule->AddBehaviour<AI::SeekBehaviour>();
	mWanderBehavior = mSteeringModule->AddBehaviour<AI::WanderBehaviour>();

	// Graphics
	for (size_t i = 0; i < mTextureIds.size(); ++i)
	{
		char name[256];
		sprintf_s(name, "scv_%02zu.png", i + 1);
		mTextureIds[i] = X::LoadTexture(name);
	}
}

void SCV::Update(float deltaTime)
{
	// Apply tuning
	mVisualSensor->viewRange = viewRange;
	mVisualSensor->viewHalfAngle = viewAngle * X::Math::kDegToRad;
	mWanderBehavior->Setup(wanderRadius, wanderDistance, wanderJitter);

	mPerceptionModule->Update(deltaTime);
	auto force = mSteeringModule->Calculate();

	auto acceleration = force / mass;
	velocity += acceleration * deltaTime;

	// Make sure we don't go above the speed limit
	if (X::Math::MagnitudeSqr(velocity) >= X::Math::Sqr(maxSpeed))
		velocity = X::Math::Normalize(velocity) * maxSpeed;

	position += velocity * deltaTime;

	// If we have any movement at all, update the heading direction
	if (X::Math::MagnitudeSqr(velocity) > 1.0f)
		heading = X::Math::Normalize(velocity);

	// Screen wrapping
	auto screenWidth = X::GetScreenWidth();
	auto screenHeight = X::GetScreenHeight();
	if (position.x < 0.0f)
		position.x += screenWidth;
	if (position.x >= screenWidth)	// position.x = 1287 - 1280
		position.x -= screenWidth;	// position.x = 7
	if (position.y < 0.0f)
		position.y += screenHeight;
	if (position.y > screenHeight)
		position.y -= screenHeight;

	const auto& memoryRecords = mPerceptionModule->GetMemoryRecords();
	for (auto& memory : memoryRecords)
	{
		auto pos = memory.GetProperty<X::Math::Vector2>("lastSeenPosition");
		X::DrawScreenLine(position, pos, X::Colors::Coral);

		std::string score;
		score += std::to_string(memory.importance);
		X::DrawScreenText(score.c_str(), pos.x, pos.y, 12.0f, X::Colors::White);
	}
}

void SCV::Render()
{
	float angle = atan2(-heading.x, heading.y) + X::Math::kPi;				// 0 to 2Pi
	float percent = angle / X::Math::kTwoPi;								// 0 to 1
	int frame = (int)(percent * mTextureIds.size()) % mTextureIds.size();	// 0 to 15
	X::DrawSprite(mTextureIds[frame], position);

	X::DrawScreenCircle(destination, 30.0f, X::Colors::Red);
}

void SCV::SetDebug(bool debug)
{
	mSeekBehavior->ShowDebug(debug);
	mWanderBehavior->ShowDebug(debug);
}