#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "../Entities/Texture.h"
#include "../Timer.h"

class Asteroid : public GameEntity
{
private:
	Timer* mTimer;

	Texture* mAsteroidTexture;

	float mSpeed;

	enum START_SIDE {left = 0, right = 1, top = 2, bottom = 3};

	void SetStartPos();

	bool crossedIntoPlayArea;

	float coefficient;

	START_SIDE startSide;

public:
	Asteroid(int side);
	~Asteroid();

	void Update();
	void Render();

public:
};
#endif
