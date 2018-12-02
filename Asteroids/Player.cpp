#include "Player.h"
#include <math.h>

Player::Player()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mShip = new Texture("Ship.png");
	mShip->Parent(this);
	mShip->Pos(VEC2_ZERO);
	mShip->Scale(Vector2(0.3f, 0.3f));

	mCurrentHeading = VEC2_UP;

	currentDirection = north;

	mVisible = true;
	mWasHit = false;

	mScore = 0;
	mLives = 3;

	mSpeed = VEC2_ZERO;
}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mShip;
	mShip = NULL;
}



void Player::Update()
{
	if (mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		Rotation(Rotation(world) - 5.0f);
	} else if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Rotation(Rotation(world) + 5.0f);
	}

	if (mInput->KeyDown(SDL_SCANCODE_UP))
	{
		if (mSpeed < maxSpeed)
		{
			mSpeed += Vector2(5.0f, 5.0f);
		}

		float radRotation = Rotation(local) * 3.1415f / 180.0f;
		mCurrentHeading = Vector2(std::sin(radRotation), -std::cos(radRotation));
	}

	Translate(mCurrentHeading * mSpeed * mTimer->DeltaTime(), world);
}

void Player::Render()
{
	mShip->Render();
}