#ifndef _ASTEROIDMANAGER_H
#define _ASTEROIDMANAGER_H

#include "../Asteroids/Asteroid.h"
#include "../Entities/GameEntity.h"
#include <vector>

using namespace std;

class AsteroidManager : public GameEntity
{
private:
	const int MAX_ASTEROIDS = 5;

	static AsteroidManager* sInstance;
	vector<Asteroid*> mAsteroids;

public:
	static AsteroidManager* Instance();
	static void Release();

	void Update();
	void Render();

private:
	AsteroidManager();
	~AsteroidManager();
};
#pragma once
#endif // 
