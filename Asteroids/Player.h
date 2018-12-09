#ifndef _PLAYER_H
#define _PLAYER_H

#include "../Entities/GameEntity.h"
#include "../Managers/InputManager.h"
#include "../Timer.h"
#include "../Managers/AudioManager.h"
#include "../Entities/Texture.h"
#include "Bullet.h"
#include <math.h>
#include <string.h>

class Player : public PhysicsEntity
{
private:

	const int OFFSCREEN_BUFFER = 25;

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	static const int MAX_BULLETS = 4;

	Bullet* mBullets[MAX_BULLETS];

	Vector2 mCurrentHeading;

	Texture* mShip;

	bool mVisible;
	bool mWasHit;

	enum DIRECTIONS {north, south, east, west};

	DIRECTIONS currentDirection;

	int mScore;
	int mLives;

	Vector2 mSpeed;
	const Vector2 maxSpeed = Vector2(600.0f, 600.0f);

private:

	void HandleMovement();
	void HandleFiring();
	void HandleRotation();

	void HandleAccelerate();

	bool IgnoreCollisions() override;

public:
	Player();
	~Player();

	void Visible(bool visible);

	void Hit(PhysicsEntity* other) override;

	void ResetHit();
	void ResetSpeed();

	int GetLives();

	bool WasHit();

	void Update();
	void Render();
};
#pragma once
#endif // _PLAYER_H
