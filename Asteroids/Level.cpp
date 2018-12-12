#include "Level.h"
#include "../Physics/BoxCollider.h"

Level::Level(Player* player)
{
	mTimer = Timer::Instance();

	mStageStarted = false;

	mPlayer = player;
	mPlayer->ReloadBullets();
	mPlayerHit = false;
	mPlayerRespawnDelay = 3.0f;
	mPlayerRespawnTimer = 0.0f;
	mPlayerRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new Texture("GAME OVER", "emulogic.ttf", 32, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mReadyLabelTimer = 0.0f;
	mReadyLabelDelay = 3.0f;

	mReadyLabel = new Texture("READY", "emulogic.ttf", 32, { 150, 0, 0 });
	mReadyLabel->Parent(this);
	mReadyLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mCurrentState = running;
	
	mAsteroids = AsteroidManager::Instance();
	mAsteroids->SetCurrentPlayer(mPlayer);
	mAsteroids->Reset();

	mNoCollisionsHere = new PhysicsEntity();
	mNoCollisionsHere->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mNoCollisionsHere->AddCollider(new BoxCollider(Vector2(100.0f, 100.0f)));
}

Level::~Level()
{
	mTimer = NULL;
	mAsteroids = NULL;

	mPlayer = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;
}

void Level::StartStage()
{
	mStageStarted = true;
}

void Level::HandleCollisions()
{
	if (!mPlayerHit)
	{
		if (mPlayer->WasHit())
		{
			mPlayerHit = true;
			mPlayer->Active(false);
			mPlayerRespawnTimer = 0.0f;
		}
	}
}

void Level::HandlePlayerDeath()
{
	if (mPlayer->GetLives() > 0)
	{
		if (mPlayerRespawnTimer == 0.0f)
		{
			mPlayer->Visible(false);
		}

		mPlayerRespawnTimer += mTimer->DeltaTime();
		if (mPlayerRespawnTimer >= mPlayerRespawnDelay)
		{
			bool noCollision = true;
			for (int i = 0; i < mAsteroids->mAsteroids.size(); ++i)
			{
				if (mNoCollisionsHere->CheckCollision(mAsteroids->mAsteroids[i]))
				{
					noCollision = false;
				}
			}

			if (noCollision == true)
			{
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				mPlayer->ResetHit();
				mPlayer->ResetSpeed();
				mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));
				mPlayerRespawnTimer = 0.0f;
			}
		}
	} else
	{
		if (mGameOverTimer == 0.0f)
		{
			mPlayer->Visible(false);
		}

		mGameOverTimer += mTimer->DeltaTime();
		if (mGameOverTimer >= mGameOverDelay)
		{
			mCurrentState = gameOver;
			mAsteroids->Reset();
		}
	}
}

Level::LEVEL_STATES Level::CurrentState()
{
	return mCurrentState;
}

void Level::Update()
{
	if (mStageStarted)
	{
		HandleCollisions();

		if (mPlayerHit)
		{
			HandlePlayerDeath();
		}

		if (mAsteroids->mAsteroids.size() == 0)
		{
			mCurrentState = finished;
		}
	}
	else
	{
		mReadyLabelTimer += mTimer->DeltaTime();
		if (mReadyLabelTimer >= mReadyLabelDelay)
		{
			StartStage();
			mPlayer->Active(true);
			mPlayer->Visible(true);
		}
	}
}

void Level::Render()
{
	if (mStageStarted)
	{
		if (mPlayerHit)
		{
			if (mGameOverTimer >= mGameOverLabelOnScreen)
				mGameOverLabel->Render();
		}
	} 
	else
	{
		if (mReadyLabelTimer < mReadyLabelDelay)
			mReadyLabel->Render();
	}
}