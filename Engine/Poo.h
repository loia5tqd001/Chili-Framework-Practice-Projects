#pragma once
#include "GameObject.h"
#include "Dude.h"

#define POO_WIDTH 24
#define POO_HEIGHT 24

class Poo : public GameObject
{
private:
	bool IsCollide(const Dude& dude) const;

public:
	Poo(int screenWidth, int screenHeight, const Dude& dude);
	bool Move(const Dude& dude);
	void Draw(Graphics& gfx) const override;

private:
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	int vx;
	int vy;
};

