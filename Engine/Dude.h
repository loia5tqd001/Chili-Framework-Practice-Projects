#pragma once
#include "GameObject.h"

#define DUDE_WIDTH 20
#define DUDE_HEIGHT 20

#define MOVE_LEFT  1
#define MOVE_UP    2
#define MOVE_RIGHT 4
#define MOVE_DOWN  8

class Dude : public GameObject
{
private:
	Dude(int screenWidth, int screenHeight);

public:
	int GetX() const;
	int GetY() const;
	static Dude& GetInstance(int screenWidth, int screenHeight);
	void Move(int direction, float dt);
	void Draw(Graphics& gfx) const override;
	void Reset();

private:
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	static constexpr int SPEED = 300;
};

