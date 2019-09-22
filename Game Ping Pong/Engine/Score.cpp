#include "Score.h"



Score::Score(int x, int y) :
	x(x),
	y(y)
{
}

void Score::Draw(Graphics & gfx) const
{
	if (value < 10)
	{
		int midX = gfx.ScreenWidth / 2;
		if (x < midX)
		{
			int _x = x + 30;
			gfx.DrawDigit(value, _x, y, 0, 0, 255);
		}
		else {
			gfx.DrawDigit(value, x, y, 0, 0, 255);
		}
	}
	else if (value < 100)
	{
		gfx.DrawDigit(value / 10, x, y, 0, 0, 255);
		gfx.DrawDigit(value % 10, x + 30, y, 0, 0, 255);
	}
}

void Score::Increase()
{
	value++;
}

void Score::Reset()
{
	value = 0;
}

Score & Score::GetScorePlayer1(const Playground & ground)
{
	static Score instance(ground.X_MIN + (ground.X_MAX-ground.X_MIN) / 2 - 70, ground.Y_MIN + 15);
	return instance;
}

Score & Score::GetScorePlayer2(const Playground & ground)
{
	static Score instance(ground.X_MIN + (ground.X_MAX - ground.X_MIN) / 2 + 15, ground.Y_MIN + 15);
	return instance;
}

