#pragma once
#include "Playground.h"
#include "Paddle.h"
#include "Random.h"

#define P1_SCORE 1
#define P2_SCORE 2
#define NO_SCORE 3
#define SCORE_STATUS int

class Ball
{
private:
	Ball(const Playground& ground);
	bool Collide(const Paddle& p) const;

public:
	static Ball& GetInstance(const Playground& ground);
	SCORE_STATUS Move(const Paddle& p1, const Paddle& p2);
	void Draw(Graphics& gfx) const;
	void Reset(SCORE_STATUS whoScored);
	int AiDirection(const Paddle& p) const;

public:
	const int WIDTH = 20;
	const int HEIGHT = 20;

private:
	const Playground &ground;
	int x;
	int y;
	int vx;
	int vy;
};

