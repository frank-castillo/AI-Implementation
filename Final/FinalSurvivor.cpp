#include "FinalSurvivor.h"
#include "FinalSurvivorStates.h"
#include "IDTypesFinal.h"

extern float viewRange;
extern float viewAngle;

extern float playerWanderJitter;
extern float playerWanderRadius;
extern float playerWanderDistance;

namespace
{
	float ComputeImportance(const AI::Agent& agent, const AI::MemoryRecord& record)
	{
		float distance = X::Math::Distance(agent.position, record.GetProperty<X::Math::Vector2>("lastSeenPosition"));
		float distanceScore = 10000.0f - distance;
		return distanceScore;
	}
}

Survivor::Survivor(AI::AIWorld& world)
	: Agent(world, EntityTypes::SurvivorType)
{

}

void Survivor::Load()
{
	mPerceptionModule = std::make_unique<AI::PerceptionModule>(*this, ComputeImportance);
	mVisualSensor = mPerceptionModule->AddSensor<VisualSensor>();
	mPerceptionModule->SetMemorySpan(60.0f);

	mStateMachine = std::make_unique<AI::StateMachine<Survivor>>(*this);
	mStateMachine->AddState<SurvivorWander>();
	mStateMachine->AddState<SurvivorRun>();
	mStateMachine->AddState<SurvivorGetAmmo>();
	mStateMachine->ChangeState(Wander);

	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehaviour = mSteeringModule->AddBehaviour<AI::SeekBehaviour>();
	mFleeBehaviour = mSteeringModule->AddBehaviour<AI::FleeBehaviour>();
	mArriveBehaviour = mSteeringModule->AddBehaviour<AI::ArriveBehaviour>();
	mPursuitBehaviour = mSteeringModule->AddBehaviour<AI::PursuitBehaviour>();
	mWanderBehaviour = mSteeringModule->AddBehaviour<AI::WanderBehaviour>();

	mSeekBehaviour->SetActive(false);
	mFleeBehaviour->SetActive(false);
	mFleeBehaviour->SetPanicDistance(100.f);
	mArriveBehaviour->SetActive(false);
	mPursuitBehaviour->SetActive(false);
	mWanderBehaviour->SetActive(true);

	maxSpeed = 250.0f;

	mTextureId = X::LoadTexture("survivor_handgun.png");
	mSpriteWidth = static_cast<float>(X::GetSpriteWidth(mTextureId));
	mSpriteHeight = static_cast<float>(X::GetSpriteHeight(mTextureId));
	mHalfSpriteWidth = mSpriteWidth / 2.0f;
}

void Survivor::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);

	if (mWanderBehaviour->IsActive())
	{
		mWanderBehaviour->Setup(playerWanderRadius, playerWanderDistance, playerWanderJitter);
	}

	// Apply tuning
	mVisualSensor->viewRange = viewRange;
	mVisualSensor->viewHalfAngle = viewAngle * X::Math::kDegToRad;

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

void Survivor::Render()
{
	float angle = atan2(heading.y, heading.x);
	X::DrawSprite(mTextureId, position, angle);
	X::DrawScreenCircle(GetBoundingCircle(), X::Colors::Red);
}

void Survivor::ChangeState(State state)
{
	mStateMachine->ChangeState(state);
}

void Survivor::SetDebug(bool active)
{
	mSeekBehaviour->ShowDebug(active);
	mFleeBehaviour->ShowDebug(active);
	mArriveBehaviour->ShowDebug(active);
	mPursuitBehaviour->ShowDebug(active);
	mWanderBehaviour->ShowDebug(active);
}