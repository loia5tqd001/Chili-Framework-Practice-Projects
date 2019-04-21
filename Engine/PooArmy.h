#pragma once
#include "Poo.h"

class PooArmy
{
private:
	PooArmy(int screenWidth, int screenHeight, const Dude& dude);

public:
	void Reset(const Dude& dude);
	bool Move(const Dude& dude);
	static PooArmy& GetInstance(int screenWidth, int screenHeight, const Dude& dude);
	void Draw(Graphics& gfx) const;
	void Aid(const Dude& dude);

private:
	std::vector<Poo> poos;
	int nPoo;
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
};

