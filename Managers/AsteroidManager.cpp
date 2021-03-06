#include "AsteroidManager.h"

AsteroidManager* AsteroidManager::sInstance = NULL;
Player* AsteroidManager::sPlayer = nullptr;

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
	for (int i = 0; i < 5; ++i)
	{
		mAsteroids.push_back(new Asteroid(rand() % 4));
	}

	mAudio = AudioManager::Instance();
}

void AsteroidManager::SetCurrentPlayer(Player* player)
{
	sPlayer = player;
}

AsteroidManager::~AsteroidManager()
{
	Reset();
}

void AsteroidManager::Reset()
{
	for (int i = 0; i < mAsteroids.size(); ++i)
	{
		delete mAsteroids[i];
		mAsteroids[i] = NULL;
	}

	mAsteroids.resize(5);

	for (int i = 0; i < 5; ++i)
	{
		mAsteroids[i] = new Asteroid(rand() % 4);
	}
}

void AsteroidManager::Update()
{
	for (int i = 0; i < mAsteroids.size(); ++i)
	{
		if (mAsteroids[i]->Active())
		{
			mAsteroids[i]->Update();
		}
	}

	for (int i = 0; i < mAsteroids.size(); ++i)
	{
		if (mAsteroids[i]->GetCurrentState() == Asteroid::destroyed)
		{
			Asteroid* asteroid = mAsteroids[i];
			Vector2 pos = asteroid->Pos(world);
			Asteroid::SIZE size = asteroid->GetSize();

			switch (size)
			{
				case Asteroid::large:
					size = Asteroid::medium;
					mAudio->PlaySFX("bangLarge.wav");
					sPlayer->AddScore(20);
					break;

				case Asteroid::medium:
					size = Asteroid::small;
					mAudio->PlaySFX("bangMedium.wav");
					sPlayer->AddScore(50);
					break;

				case Asteroid::small:
					delete mAsteroids[i];
					mAudio->PlaySFX("bangSmall.wav");
					mAsteroids.erase(mAsteroids.begin() + i);
					sPlayer->AddScore(100);
					return;
			}

			for (int i = 0; i < 3; ++i)
			{
				mAsteroids.push_back(new Asteroid(size));
				mAsteroids[mAsteroids.size() - 1]->Pos(pos);
			}

			delete mAsteroids[i];
			mAsteroids.erase(mAsteroids.begin() + i);
		}
	}
}

void AsteroidManager::Render()
{
	for (int i = 0; i < mAsteroids.size(); ++i)
	{
		if (mAsteroids[i]->Active())
		{
			mAsteroids[i]->Render();
		}
	}
}