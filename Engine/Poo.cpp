#include "Poo.h"

Poo::Poo(int screenWidth, int screenHeight, const Dude& dude) :
	SCREEN_WIDTH(screenWidth),
	SCREEN_HEIGHT(screenHeight)
{
	do 
	{
		x = Random::Next(0, SCREEN_WIDTH - POO_WIDTH);
		y = Random::Next(40, SCREEN_HEIGHT - POO_HEIGHT);
	} 
	while (IsCollide(dude));
	
	do {
		vx = Random::Next(-3, 3);
	} 
	while( vx == 0);

	do {
		vy = Random::Next(-3, 3);
	}
	while (vy == 0);
}

bool Poo::Move(const Dude& dude)
{
	x += vx;
	y += vy;

	if (x < 0)
	{
		x = 0;
		vx = -vx;
	}
	else if (x + POO_WIDTH > SCREEN_WIDTH)
	{
		x = SCREEN_WIDTH - POO_WIDTH;
		vx = -vx;
	}

	if (y < 40)
	{
		y = 40;
		vy = -vy;
	}
	else if (y + POO_HEIGHT > SCREEN_HEIGHT)
	{
		y = SCREEN_HEIGHT - POO_HEIGHT;
		vy = -vy;
	}

	return !IsCollide(dude);
}

void Poo::Draw(Graphics & gfx) const
{
	#include "poo (24x24).txt"
}

bool Poo::IsCollide(const Dude & dude) const
{
	const int left0 = x;
	const int top0 = y;
	const int right0 = left0 + POO_WIDTH;
	const int bottom0 = top0 + POO_HEIGHT;

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
