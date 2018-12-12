#include "Asteroid.h"
#include "../Physics/BoxCollider.h"
#include "../Managers/PhysicsManager.h"

Asteroid::Asteroid(int side)
{
	mTimer = Timer::Instance();

	mSize = SIZE::large;

	mAsteroidTexture = new Texture("Asteroid1.png");
	mAsteroidTexture->Parent(this);

	startSide = START_SIDE(side);

	mSpeed = 100.0f;

	crossedIntoPlayArea = false;
	coefficient = -1.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f + 1.0f)));

	SetStartPos();

	AddCollider(new BoxCollider(mAsteroidTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	mCurrentState = spawned;

	mPhysics = PhysicsManager::Instance();
}

Asteroid::Asteroid(SIZE size)
{
	mTimer = Timer::Instance();

	mSize = size;

	if (size == medium)
	{
		mAsteroidTexture = new Texture("Asteroid2.png");
	} else if (size == small)
	{
		mAsteroidTexture = new Texture("Asteroid3.png");
	}

	mAsteroidTexture->Parent(this);
	mAsteroidTexture->Pos(VEC2_ZERO);

	mSpeed = 100.0f;

	startSide = START_SIDE(rand() % 4);

	crossedIntoPlayArea = false;
	coefficient = -1.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f + 1.0f)));

	AddCollider(new BoxCollider(mAsteroidTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	mCurrentState = spawned;

	mPhysics = PhysicsManager::Instance();
}

Asteroid::~Asteroid()
{
	mTimer = NULL;

	PhysicsManager::Instance()->UnregisterEntity(mId);

	delete mAsteroidTexture;
	mAsteroidTexture = NULL;
}

void Asteroid::SetStartPos()
{
	Graphics* mGraphics = Graphics::Instance();

	switch (startSide)
	{
		case left:
			Pos(Vector2(-50.0f, rand() % mGraphics->SCREEN_HEIGHT));
			break;
		case right:
			Pos(Vector2(mGraphics->SCREEN_WIDTH + 50.0f, rand() % mGraphics->SCREEN_HEIGHT));
			break;
		case top:
			Pos(Vector2(rand() % mGraphics->SCREEN_WIDTH, -50.0f));
			break;
		case bottom:
			Pos(Vector2(rand() % mGraphics->SCREEN_WIDTH, mGraphics->SCREEN_HEIGHT + 50.0f));
			break;
	}
}

void Asteroid::Hit(PhysicsEntity* other)
{
	if (mPhysics->GetCollisionLayer(other->GetId()) == PhysicsManager::CollisionLayers::FriendlyProjectiles)
	{
		mCurrentState = destroyed;
	}
}


bool Asteroid::IgnoreCollisions()
{
	return !Active();
}

Asteroid::SIZE Asteroid::GetSize()
{
	return mSize;
}

Asteroid::CURRENT_STATE Asteroid::GetCurrentState()
{
	return mCurrentState;
}

void Asteroid::Update()
{
	Graphics* mGraphics = Graphics::Instance();

	switch (startSide)
	{
		case left:
			Translate(Vector2(1.0f, coefficient) * mSpeed * mTimer->DeltaTime(), world);
			break;
		case right:
			Translate(Vector2(-1.0f, coefficient) * mSpeed * mTimer->DeltaTime(), world);
			break;
		case top:
			Translate(Vector2(coefficient, 1.0f) * mSpeed * mTimer->DeltaTime(), world);
			break;
		case bottom:
			Translate(Vector2(coefficient, -1.0f) * mSpeed * mTimer->DeltaTime(),world);
			break;
	}

	if (Pos().x > mGraphics->SCREEN_WIDTH + OFFSCREEN_BUFFER)
	{
		Pos(Vector2(0.0f, Pos().y));
	} 
	else if (Pos().x < -OFFSCREEN_BUFFER)
	{
		Pos(Vector2(mGraphics->SCREEN_WIDTH + OFFSCREEN_BUFFER, Pos().y));
	}

	if (Pos().y > mGraphics->SCREEN_HEIGHT + OFFSCREEN_BUFFER)
	{
		Pos(Vector2(Pos().x, -OFFSCREEN_BUFFER));
	} 
	else if (Pos().y < -OFFSCREEN_BUFFER)
	{
		Pos(Vector2(Pos().x, mGraphics->SCREEN_HEIGHT + OFFSCREEN_BUFFER));
	}
}

void Asteroid::Render()
{
	mAsteroidTexture->Render();
}