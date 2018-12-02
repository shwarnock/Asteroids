#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid(int side)
{
	mTimer = Timer::Instance();

	mAsteroidTexture = new Texture("Asteroid1.png");
	mAsteroidTexture->Parent(this);

	startSide = START_SIDE(side);

	mSpeed = 100.0f;

	crossedIntoPlayArea = false;
	coefficient = -1.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f + 1.0f)));

	SetStartPos();
}

Asteroid::~Asteroid()
{
	mTimer = NULL;
}

void Asteroid::SetStartPos()
{
	Graphics* mGraphics = Graphics::Instance();

	switch (startSide)
	{
		case left:
			Pos(Vector2(-50.0f, rand() % mGraphics->SCREEN_HEIGHT));
			break;
		case right:
			Pos(Vector2(mGraphics->SCREEN_WIDTH + 50.0f, rand() % mGraphics->SCREEN_HEIGHT));
			break;
		case top:
			Pos(Vector2(rand() % mGraphics->SCREEN_WIDTH, -50.0f));
			break;
		case bottom:
			Pos(Vector2(rand() % mGraphics->SCREEN_WIDTH, mGraphics->SCREEN_HEIGHT + 50.0f));
			break;
	}
}

void Asteroid::Update()
{
	Graphics* mGraphics = Graphics::Instance();

	switch (startSide)
	{
		case left:
			Translate(Vector2(1.0f, coefficient) * mSpeed * mTimer->DeltaTime(), world);
			break;
		case right:
			Translate(Vector2(-1.0f, coefficient) * mSpeed * mTimer->DeltaTime(), world);
			break;
		case top:
			Translate(Vector2(coefficient, 1.0f) * mSpeed * mTimer->DeltaTime(), world);
			break;
		case bottom:
			Translate(Vector2(coefficient, -1.0f) * mSpeed * mTimer->DeltaTime(),world);
			break;
	}

	if (Pos().x > mGraphics->SCREEN_WIDTH + 50.0f)
	{
		Pos(Vector2(0.0f, Pos().y));
	} 
	else if (Pos().x < - 50.0f)
	{
		Pos(Vector2(mGraphics->SCREEN_WIDTH + 50.0f, Pos().y));
	}

	if (Pos().y > mGraphics->SCREEN_HEIGHT + 50.0f)
	{
		Pos(Vector2(Pos().x, -50.0f));
	} 
	else if (Pos().y < -50.0f)
	{
		Pos(Vector2(Pos().x, mGraphics->SCREEN_HEIGHT + 50.0f));
	}
}

void Asteroid::Render()
{
	mAsteroidTexture->Render();
}