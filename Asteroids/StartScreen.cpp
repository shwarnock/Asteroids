#include "StartScreen.h"

using namespace std;

StartScreen::StartScreen()
{
	string font = "emulogic.ttf";

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	Pos(VEC2_ZERO);

	//Bottom Bar Entities
	mBottomBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT - 200.0f));
	mPressStart = new Texture("Press Enter to Start", font, 20, {255, 255, 255});
	mAtari = new Texture("1979 ATARI INC", font, 12, { 255, 255, 255 });

	mPressStart->Parent(mBottomBar);
	mAtari->Parent(mBottomBar);

	mPressStart->Pos(VEC2_ZERO);
	mAtari->Pos(Vector2(0.0f, 80.0f));
}

StartScreen::~StartScreen()
{
	delete mBottomBar;
	mBottomBar = NULL;
	delete mPressStart;
	mPressStart = NULL;
	delete mAtari;
	mAtari = NULL;

	mTimer = NULL;
	mInput = NULL;
}

void StartScreen::Render()
{
	mPressStart->Render();
	mAtari->Render();
}

void StartScreen::Update()
{

}