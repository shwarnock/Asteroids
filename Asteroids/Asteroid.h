#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "../Entities/Texture.h"
#include "../Timer.h"
#include "../Physics/PhysicsEntity.h"

class Asteroid : public PhysicsEntity
{
public:
	enum SIZE { small, medium, large };
	enum CURRENT_STATE { spawned, destroyed, unspawned };

private:

	const int OFFSCREEN_BUFFER = 35;

	Timer* mTimer;

	Texture* mAsteroidTexture;

	float mSpeed;

	enum START_SIDE {left = 0, right = 1, top = 2, bottom = 3};

	void SetStartPos();

	bool crossedIntoPlayArea;

	float coefficient;

	START_SIDE startSide;

	SIZE mSize;

	CURRENT_STATE mCurrentState;

public:
	
	Asteroid(int side);
	Asteroid(SIZE size);

	~Asteroid();

	void Hit(PhysicsEntity* other) override;

	SIZE GetSize();

	CURRENT_STATE GetCurrentState();

	void Update();
	void Render();

private:
	bool IgnoreCollisions() override;
};
#endif
