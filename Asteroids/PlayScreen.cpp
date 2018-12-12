#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	Pos(VEC2_ZERO);

	mPlayerOneScore = new ScoreBoard();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Pos(Vector2(200.0f, 50.0f));

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

	mPlayer = NULL;

	mLevel = NULL;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mLevelStartDelay = 1.0f;
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mPlayer;
	mPlayer = NULL;

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
	mPlayer->Active(false);
	mPlayer->Visible(false);
	mPlayer->Parent(this);

	SetShips(mPlayer->GetLives());
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mGameStarted = false;
	mLevelStarted = false;
}

void PlayScreen::SetPlayerScore(int score)
{
	mPlayerOneScore->Score(score);
}

void PlayScreen::SetShips(int ships)
{
	mTotalShips = ships;
}

bool PlayScreen::GameOver()
{
	if (!mLevelStarted)
	{
		return false;
	}

	return mLevel->CurrentState() == Level::gameOver;
}

void PlayScreen::StartNextLevel()
{
	mLevelStarted = true;

	mPlayer->Active(false);
	mPlayer->Visible(false);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));
	
	delete mLevel;
	mLevel = new Level(mPlayer);
}

void PlayScreen::Update()
{
	if (mGameStarted)
	{
		mPlayer->Update();

		if (!mLevelStarted)
		{
			StartNextLevel();
		}
		else
		{
			mLevel->Update();
			if (mLevel->CurrentState() == Level::finished)
			{
				mLevelStarted = false;
				mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));
				mPlayer->Active(false);
				mPlayer->Pos(false);
			}
		}


		SetPlayerScore(mPlayer->GetScore());
	} else
	{
		mGameStarted = true;
	}
}

void PlayScreen::Render()
{
	if (mLevelStarted)
	{
		mLevel->Render();
	}
	mPlayer->Render();
	mPlayerOneScore->Render();

	for (int i = 0; i < 3 && i < mPlayer->GetLives(); ++i)
	{
		mShipTextures[i]->Render();
	}

}