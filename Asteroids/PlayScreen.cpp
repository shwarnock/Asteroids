#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	mAsteroids = AsteroidManager::Instance();

	Pos(VEC2_ZERO);

	mPlayer = NULL;
	mPlayerRespawnTimer = 0.0f;
	mPlayerRespawnDelay = 3.0f;

	mGameOverLabel = new Texture("GAME OVER", "emulogic.ttf", 32, { 250, 250, 250 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));

	mGameOver = false;
	mGameOverDelay = 6.0f;
	mGameoverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = running;

	mPlayerOneScore = new ScoreBoard();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Pos(Vector2(80.0f, 50.0f));

	mShips = new GameEntity();
	mShips->Parent(this);
	mShips->Pos(Vector2(50.0f, 100.0f));

	for (int i = 0; i < 3; ++i)
	{
		mShipTextures[i] = new Texture("Ship.png");
		mShipTextures[i]->Parent(mShips);
		mShipTextures[i]->Pos(Vector2(30 * (i % 3), 0));
		mShipTextures[i]->Scale(Vector2(0.3f, 0.3f));
	}
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;
	mAsteroids = NULL;

	delete mPlayer;
	mPlayer = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;

	delete mPlayerOneScore;
	mPlayerOneScore = NULL;

	delete mShips;
	mShips = NULL;

	for (int i = 0; i < 3; ++i)
	{
		delete mShipTextures[i];
		mShipTextures[i] = NULL;
	}
}

void PlayScreen::StartNewGame()
{
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Active(true);
	mPlayer->Visible(true);
	mPlayer->Parent(this);
	SetShips(mPlayer->GetLives());
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mGameoverTimer = 0.0f;
	mPlayerHit = false;
	mCurrentState = running;
}

void PlayScreen::SetPlayerScore(int score)
{
	mPlayerOneScore->Score(score);
}

void PlayScreen::SetShips(int ships)
{
	mTotalShips = ships;
}

void PlayScreen::HandleCollisions()
{
	if (!mPlayerHit)
	{
		if (mPlayer->WasHit())
		{

			SetShips(mPlayer->GetLives());
			mPlayerHit = true;
			mPlayer->Active(false);
		}
	}
}

void PlayScreen::HandlePlayerDeath()
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
				if (mPlayer->CheckCollision(mAsteroids->mAsteroids[i]))
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
		if (mGameoverTimer == 0.0f)
		{
			mPlayer->Visible(false);
		}

		mGameoverTimer += mTimer->DeltaTime();
		if (mGameoverTimer >= mGameOverDelay)
		{
			mCurrentState = gameOver;
			mAsteroids->Reset();
		}
	}
}

PlayScreen::LEVEL_STATES PlayScreen::GetCurrentState()
{
	return mCurrentState;
}

bool PlayScreen::GameOver()
{
	return mCurrentState == LEVEL_STATES::gameOver;
}

void PlayScreen::Update()
{
	mPlayer->Update();

	HandleCollisions();

	if (mPlayerHit)
	{
		HandlePlayerDeath();
	}
}

void PlayScreen::Render()
{
	if (mCurrentState == running)
	{
		mPlayer->Render();
		mPlayerOneScore->Render();

		for (int i = 0; i < 3 && i < mTotalShips; ++i)
		{
			mShipTextures[i]->Render();
		}
	}

	if (mGameoverTimer >= mGameOverLabelOnScreen)
	{
		mGameOverLabel->Render();
	}
}