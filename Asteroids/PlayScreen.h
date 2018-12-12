#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H

#include "../Entities/GameEntity.h"
#include "../Managers/InputManager.h"
#include "../Timer.h"
#include "../Managers/AudioManager.h"
#include "../Asteroids/Player.h"
#include "../Managers/AsteroidManager.h"
#include "ScoreBoard.h"
#include "Level.h"

class PlayScreen : public GameEntity
{

private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Player* mPlayer;

	GameEntity* mShips;
	Texture* mShipTextures[3];
	int mTotalShips;

	ScoreBoard* mPlayerOneScore;

	Level* mLevel;
	bool mLevelStarted;

	bool mGameStarted;

	float mLevelStartTimer;
	float mLevelStartDelay;

public:

	bool GameOver();

	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void SetPlayerScore(int score);
	void SetShips(int ships);

	void Render();
	void Update();

private:
	void StartNextLevel();
};
#pragma once
#endif // 
