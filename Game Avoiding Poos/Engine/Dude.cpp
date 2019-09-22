#include "Dude.h"




Dude::Dude(int screenWidth, int screenHeight) :
	SCREEN_WIDTH(screenWidth),
	SCREEN_HEIGHT(screenHeight)
{
	Reset();
}

int Dude::GetX() const
{
	return x;
}

int Dude::GetY() const
{
	return y;
}

Dude & Dude::GetInstance(int screenWidth, int screenHeight)
{
	static Dude instance(screenWidth, screenHeight);
	return instance;
}

void Dude::Move(int direction, float dt)
{
	if (direction & MOVE_LEFT)
		x -= SPEED * dt;
	if (direction & MOVE_UP)
		y -= SPEED * dt;
	if (direction & MOVE_RIGHT)
		x += SPEED * dt;
	if (direction & MOVE_DOWN)
		y += SPEED * dt;

	if (x < 0)
		x = 0;
	else if (x + DUDE_WIDTH > SCREEN_WIDTH)
		x = SCREEN_WIDTH - DUDE_WIDTH;

	if (y < 40)
		y = 40;
	else if (y + DUDE_HEIGHT > SCREEN_HEIGHT)
		y = SCREEN_HEIGHT - DUDE_HEIGHT;
}

void Dude::Draw(Graphics & gfx) const
{
	#include "face (20x20).txt"
}

void Dude::Reset()
{
	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2;
}
