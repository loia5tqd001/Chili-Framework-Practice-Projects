#include "PooArmy.h"



PooArmy::PooArmy(int screenWidth, int screenHeight, const Dude & dude) :
	SCREEN_WIDTH(screenWidth),
	SCREEN_HEIGHT(screenHeight)
{
	Reset(dude);
}

void PooArmy::Reset(const Dude & dude)
{
	if (poos.size() > 0)
	{
		poos.clear();
		poos.shrink_to_fit();
	}

	nPoo = Random::Next(5, 15);
	poos.reserve(nPoo);
	for (int i = 0; i < nPoo; i++)
	{
		poos.emplace_back(SCREEN_WIDTH, SCREEN_HEIGHT, dude);
	}
}

bool PooArmy::Move(const Dude & dude)
{
	bool isCollide = false;
	for (Poo &poo : poos)
	{
		isCollide = isCollide || !poo.Move(dude);
	}
	return !isCollide;
}

PooArmy & PooArmy::GetInstance(int screenWidth, int screenHeight, const Dude & dude)
{
	static PooArmy instance(screenWidth, screenHeight, dude);
	return instance;
}

void PooArmy::Draw(Graphics & gfx) const
{
	for (const Poo &poo : poos)
		poo.Draw(gfx);
}

void PooArmy::Aid(const Dude & dude)
{
	nPoo++;
	poos.emplace_back(SCREEN_WIDTH, SCREEN_HEIGHT, dude);
}
