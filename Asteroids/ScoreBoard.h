#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include "../Entities/GameEntity.h"
#include <vector>
#include "../Entities/Texture.h"
using namespace std;

class ScoreBoard : public GameEntity
{
private:
	vector<Texture*> mScore;

	SDL_Color mColor;

public:
	ScoreBoard();
	ScoreBoard(SDL_Color color);
	~ScoreBoard();

	void Score(int score);

	void Render();

private:
	void ClearBoard();
};

#endif // 
