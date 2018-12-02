#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H

#include "../Entities/GameEntity.h"
#include "../Managers/InputManager.h"
#include "../Timer.h"
#include "../Managers/AudioManager.h"
#include "../Asteroids/Player.h"

class PlayScreen : public GameEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Player* mPlayer;

public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void Render();
	void Update();
};
#pragma once
#endif // 
