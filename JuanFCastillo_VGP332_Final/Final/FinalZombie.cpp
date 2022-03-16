#include "FinalZombie.h"

#include "IDTypesFinal.h"

extern float zombieWanderJitter;
extern float zombieWanderRadius;
extern float zombieWanderDistance;

Zombie::Zombie(AI::AIWorld& world)
	:Agent(world, EntityTypes::ZombieType)
{
}

void Zombie::Load()
{
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mWanderBehaviour = mSteeringModule->AddBehaviour<AI::WanderBehaviour>();
	mWanderBehaviour->SetActive(true);

	maxSpeed = 150.0f;

	position = X::RandomVector2({ 500.0f, 100.0f }, { 780.0f, 710.0f });
	position.x += X::Random(0, 1) == 0 ? -300.0f : 300.0f;

	mTextureID = X::LoadTexture("zombie_idle.png");
}

void Zombie::Unload()
{
	mTextureID = 0;
}

void Zombie::Update(float deltaTime)
{
	if (mWanderBehaviour->IsActive())
	{
		mWanderBehaviour->Setup(zombieWanderRadius, zombieWanderDistance, zombieWanderJitter);
	}

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
}

void Zombie::Render()
{
	float angle = atan2(heading.y, heading.x);
	X::DrawSprite(mTextureID, position, angle);
}

void Zombie::ShowDebug(bool debug)
{
	mWanderBehaviour->ShowDebug(debug);
}
