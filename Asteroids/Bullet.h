#ifndef _BULLET_H
#define _BULLET_H

#include "../Timer.h"
#include "../Physics/PhysicsEntity.h"

class Bullet : public PhysicsEntity
{
private:

	const int OFFSCREEN_BUFFER = 10;

	const int TIME_TO_LIVE = 2;

	Texture* mBullet;
	Timer* mTimer;

	Vector2 mSpeed;

	float bulletTimer = 0.0f;

public:
	Bullet();
	~Bullet();

	void Fire(Vector2 pos, float shipRotation);
	void Reload();


	void Hit(PhysicsEntity* other) override;

	void Update();
	void Render();

private:
	bool IgnoreCollisions() override;
};

#endif // _DEBUG
