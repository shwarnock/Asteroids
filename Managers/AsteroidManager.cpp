#include "AsteroidManager.h"

AsteroidManager* AsteroidManager::sInstance = NULL;

AsteroidManager* AsteroidManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new AsteroidManager();
	}

	return sInstance;
}

void AsteroidManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

AsteroidManager::AsteroidManager()
{
	for (int i = 0; i < MAX_ASTEROIDS; ++i)
	{
		mAsteroids.push_back(new Asteroid(rand() % 4));
	}
}

AsteroidManager::~AsteroidManager()
{
	for (int i = 0; i < MAX_ASTEROIDS; ++i)
	{
		delete mAsteroids[i];
		mAsteroids[i] = NULL;
	}

	mAsteroids.clear();
}

void AsteroidManager::Update()
{
	for (int i = 0; i < MAX_ASTEROIDS; ++i)
	{
		mAsteroids[i]->Update();
	}
}

void AsteroidManager::Render()
{
	for (int i = 0; i < MAX_ASTEROIDS; ++i)
	{
		mAsteroids[i]->Render();
	}
}