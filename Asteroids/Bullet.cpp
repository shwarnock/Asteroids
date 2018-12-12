#include "Bullet.h"
#include "../Physics/BoxCollider.h"
#include "../Managers/PhysicsManager.h"

Bullet::Bullet()
{
	mTimer = Timer::Instance();

	mBullet = new Texture("Bullet.png");
	mBullet->Parent(this);
	mBullet->Pos(VEC2_ZERO);

	Reload();

	AddCollider(new BoxCollider(Vector2(8.0f, 8.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);
}

Bullet::~Bullet()
{
	mTimer = NULL;

	delete mBullet;
	mBullet = NULL;

	PhysicsManager::Instance()->UnregisterEntity(mId);
}

void Bullet::Fire(Vector2 pos, float rotation)
{
	Pos(pos);
	Active(true);
	// The direction of the bullet should be the direction in which the ship is facing
	mSpeed.x = static_cast<float>(sin(2 * M_PI * (rotation / 360)));
	mSpeed.y = static_cast<float>(-cos(2 * M_PI * (rotation / 360)));

	mSpeed.x *= 500;
	mSpeed.y *= 500;

}

void Bullet::Hit(PhysicsEntity* other)
{
	Reload();
}

void Bullet::Reload()
{
	Active(false);
}

void Bullet::Update()
{
	if (Active())
	{
		Pos(Vector2(Pos().x + mSpeed.x * mTimer->DeltaTime(), Pos().y + mSpeed.y * mTimer->DeltaTime()));

		bulletTimer += mTimer->DeltaTime() * 2;

		if (bulletTimer > TIME_TO_LIVE)
		{
			Reload();
			bulletTimer = 0.0f;
		}

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
}

void Bullet::Render()
{
	if (Active())
	{
		mBullet->Render();
	}
}

bool Bullet::IgnoreCollisions()
{
	return !Active();
}