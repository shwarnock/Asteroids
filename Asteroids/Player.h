#ifndef _PLAYER_H
#define _PLAYER_H

#include "../Entities/GameEntity.h"
#include "../Managers/InputManager.h"
#include "../Timer.h"
#include "../Managers/AudioManager.h"
#include "../Entities/Texture.h"

class Player : public GameEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

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
	void SetCurrentDirection();
public:
	Player();
	~Player();

	void Update();
	void Render();
};
#pragma once
#endif // _PLAYER_H
