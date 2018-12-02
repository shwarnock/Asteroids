#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H

#include "../Entities/GameEntity.h"
#include "../Managers/InputManager.h"
#include "../Timer.h"
#include "../Entities/Texture.h"
#include "Asteroid.h"


class StartScreen : public GameEntity
{
private:
	Timer* mTimer;

	InputManager* mInput;

	//Top Bar Entities
	GameEntity* mTopBar;

	//Bottom Bar Entities
	GameEntity* mBottomBar;
	Texture* mPressStart;
	Texture* mAtari;

public:
	StartScreen();
	~StartScreen();

	void Update();
	void Render();
};
#endif // _DEBUG
