#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	Pos(VEC2_ZERO);

	mPlayer = NULL;
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mPlayer;
	mPlayer = NULL;
}

void PlayScreen::StartNewGame()
{
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
}

void PlayScreen::Update()
{
	mPlayer->Update();
}

void PlayScreen::Render()
{
	mPlayer->Render();
}