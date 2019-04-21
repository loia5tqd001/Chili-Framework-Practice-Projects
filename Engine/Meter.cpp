#include "Meter.h"



Meter::Meter(int maxLevel) :
	MAX_LEVEL(maxLevel)
{
	Reset();
}

Meter & Meter::GetInstance(int screenWidth)
{
	int maxLevel = (screenWidth - 20) / DIMENSION;
	static Meter instance(maxLevel);
	return instance;
}

void Meter::Draw(Graphics & gfx) const
{
	gfx.DrawRectDim(x, y, level * DIMENSION, DIMENSION, Color(0, 0, 255));
}

bool Meter::Increase()
{
	if (level < MAX_LEVEL)
	{
		level++;
		return true;
	}
	return false;
}

void Meter::Reset()
{
	level = 0;
}
