#ifndef _ASTEROIDMANAGER_H
#define _ASTEROIDMANAGER_H

#include "../Asteroids/Asteroid.h"
#include "../Entities/GameEntity.h"
#include "AudioManager.h"
#include <vector>
#include "../Asteroids/Player.h"

using namespace std;

class AsteroidManager : public GameEntity
{
public:
	static AsteroidManager* Instance();
	static void Release();

	vector<Asteroid*> mAsteroids;

	AudioManager* mAudio;

	void SetCurrentPlayer(Player* player);

	void Reset();

	void Update();
	void Render();

private:

	static Player* sPlayer;

	static AsteroidManager* sInstance;

	AsteroidManager();
	~AsteroidManager();
};
#endif // 
