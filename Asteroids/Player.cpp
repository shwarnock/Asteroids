#include "Player.h"
#include "../Managers/PhysicsManager.h"
#include "../Physics/BoxCollider.h"

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

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		mBullets[i] = new Bullet();
	}

	AddCollider(new BoxCollider(Vector2(20.0f, 30.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mShip;
	mShip = NULL;

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		delete mBullets[i];
		mBullets[i] = NULL;
	}

	PhysicsManager::Instance()->UnregisterEntity(mId);
}

int Player::GetLives()
{
	return mLives;
}

void Player::Visible(bool visible)
{
	mVisible = visible;
}

bool Player::WasHit()
{
	return mWasHit;
}

void Player::Hit(PhysicsEntity* other)
{
	--mLives;
	mAudio->PlaySFX("bangSmall.wav");
	mWasHit = true;
}

void Player::HandleAccelerate()
{
	if (mInput->KeyDown(SDL_SCANCODE_UP))
	{
		if (mSpeed < maxSpeed)
		{
			// Create a normalized vector in the direction of travel
			Vector2 direction = Vector2(static_cast<float>(sin(2 * M_PI * (Rotation(world) / 360))), static_cast<float>(cos(2 * M_PI * (Rotation(world) / 360))));

			// Add to velocity vector (using minus for y because Direct2D uses 0,0 as the top-left corner instead of bottom-left)
			mSpeed.x += direction.x * 0.2;
			mSpeed.y -= direction.y * 0.2;
		}
	}
}

void Player::HandleMovement()
{
	Pos(Vector2(Pos().x + mSpeed.x, Pos().y + mSpeed.y));

	//Simplified Stokes Law
	mSpeed.x = mSpeed.x - mSpeed.x * 0.02;
	mSpeed.y = mSpeed.y - mSpeed.y * 0.02;

	Graphics* mGraphics = Graphics::Instance();

	if (Pos().x > mGraphics->SCREEN_WIDTH + OFFSCREEN_BUFFER)
	{
		Pos(Vector2(0.0f, Pos().y));
	} else if (Pos().x < -OFFSCREEN_BUFFER)
	{
		Pos(Vector2(mGraphics->SCREEN_WIDTH + OFFSCREEN_BUFFER, Pos().y));
	}

	if (Pos().y > mGraphics->SCREEN_HEIGHT + OFFSCREEN_BUFFER)
	{
		Pos(Vector2(Pos().x, -OFFSCREEN_BUFFER));
	} else if (Pos().y < -OFFSCREEN_BUFFER)
	{
		Pos(Vector2(Pos().x, mGraphics->SCREEN_HEIGHT + OFFSCREEN_BUFFER));
	}
}

void Player::HandleRotation()
{
	if (mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		Rotation(Rotation(world) - 5.0f);
	} else if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Rotation(Rotation(world) + 5.0f);
	}
}

void Player::HandleFiring()
{
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE))
	{
 		for (int i = 0; i < MAX_BULLETS; ++i)
		{
			if(!mBullets[i]->Active())
			{
				mBullets[i]->Fire(Pos(), Rotation(world));
				mAudio->PlaySFX("fire.wav");
				break;
			}
		}
	}
}

void Player::ResetSpeed()
{
	mSpeed = Vector2(0.0f, 0.0f);
}

void Player::ResetHit()
{
	mWasHit = false;
}

bool Player::IgnoreCollisions()
{
	return !mVisible;
}

void Player::Update()
{
	if (Active())
	{
		HandleRotation();

		HandleAccelerate();

		HandleMovement();

		HandleFiring();

		for (int i = 0; i < MAX_BULLETS; ++i)
		{
			mBullets[i]->Update();
		}
	}
}

void Player::Render()
{
	if (mVisible)
	{
		mShip->Render();
	}

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		mBullets[i]->Render();
	}

	PhysicsEntity::Render();
}