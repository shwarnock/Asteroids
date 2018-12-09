#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H

#include "../Entities/GameEntity.h"
#include "../Managers/InputManager.h"
#include "../Timer.h"
#include "../Managers/AudioManager.h"
#include "../Asteroids/Player.h"
#include "../Managers/AsteroidManager.h"
#include "ScoreBoard.h"

class PlayScreen : public GameEntity
{
public:
	enum LEVEL_STATES { running, gameOver };

private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;
	AsteroidManager* mAsteroids;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameoverTimer;
	float mGameOverLabelOnScreen;

	Player* mPlayer;
	bool mPlayerHit;
	float mPlayerRespawnTimer;
	float mPlayerRespawnDelay;

	LEVEL_STATES mCurrentState;

	GameEntity* mShips;
	Texture* mShipTextures[3];
	int mTotalShips;

	ScoreBoard* mPlayerOneScore;

public:

	LEVEL_STATES GetCurrentState();

	bool GameOver();

	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void SetPlayerScore(int score);
	void SetShips(int ships);

	void Render();
	void Update();

private:

	void HandleCollisions();
	void HandlePlayerDeath();
};
#pragma once
#endif // 
