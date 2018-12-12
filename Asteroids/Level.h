#ifndef _LEVEL_H
#define _LEVEL_H

#include "../Entities/GameEntity.h"
#include "../Timer.h"
#include "Player.h"
#include "../Managers/AsteroidManager.h"

class Level : public GameEntity
{
public: 
	enum LEVEL_STATES { running, gameOver, finished };

private:
	Timer* mTimer;
	AsteroidManager* mAsteroids;

	bool mStageStarted;

	int mLives;

	Player* mPlayer;
	bool mPlayerHit;
	float mPlayerRespawnDelay;
	float mPlayerRespawnTimer;
	float mPlayerRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	Texture* mReadyLabel;
	float mReadyLabelTimer;
	float mReadyLabelDelay;

	LEVEL_STATES mCurrentState;

	PhysicsEntity* mNoCollisionsHere;

private:
	void StartStage();

	void HandleCollisions();
	void HandlePlayerDeath();

public:
	Level(Player* player);
	~Level();

	LEVEL_STATES CurrentState();

	void Update();
	void Render();
};

#endif // 
