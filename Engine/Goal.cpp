#include "Goal.h"




Goal::Goal(int screenWidth, int screenHeight, const Dude & dude) :
	SCREEN_WIDTH(screenWidth),
	SCREEN_HEIGHT(screenHeight)
{
	Reposition(dude);
}

void Goal::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim(x, y, GOAL_WIDTH, GOAL_HEIGHT, r, 255, 255);
}

bool Goal::IsEaten(const Dude & dude) const
{
	const int left0 = x;
	const int top0 = y;
	const int right0 = left0 + GOAL_WIDTH;
	const int bottom0 = top0 + GOAL_HEIGHT;

	const int left1 = dude.GetX();
	const int top1 = dude.GetY();
	const int right1 = left1 + DUDE_WIDTH;
	const int bottom1 = top1 + DUDE_HEIGHT;

	return
		right0 > left1 &&
		left0 < right1 &&
		bottom0 > top1 &&
		top0 < bottom1;
}

void Goal::ChangeColor()
{
	if (isIncresing == true)
	{
		r += 5;
		if (r > 255)
		{
			r = 255;
			isIncresing = false;
		}
	}
	else // decreasing
	{
		r -= 5;
		if (r < 0)
		{
			r = 0;
			isIncresing = true;
		}
	}
}

void Goal::Render(Graphics & gfx)
{
	ChangeColor();
	Draw(gfx);
}

Goal & Goal::GetInstance(int screenWidth, int screenHeight, const Dude & dude)
{
	static Goal instance(screenWidth, screenHeight, dude);
	return instance;
}

void Goal::Reposition(const Dude & dude)
{
	do
	{
		x = Random::Next(0, SCREEN_WIDTH - GOAL_WIDTH);
		y = Random::Next(40, SCREEN_HEIGHT - GOAL_HEIGHT);
	}
	while (IsEaten(dude));
}
