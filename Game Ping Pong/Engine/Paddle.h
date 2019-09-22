#pragma once
#include "Playground.h"

#define MOVE_UP 1
#define MOVE_DOWN 2

class Paddle
{
private:
	Paddle(int x, int y, const Playground& ground);

public:					 
	int GetX() const;
	int GetY() const;
	int Inertia() const;
	static Paddle& GetPaddle1(const Playground& ground);
	static Paddle& GetPaddle2(const Playground& ground);
	void Move(int direction);
	void Draw(Graphics& gfx, Color color) const;
	void Reset();

public:
	static constexpr int WIDTH = 10;
	static constexpr int HEIGHT = 80;

private:
	const Playground& ground;
	const int x;
	int y;
	int lastY = 0;
	static constexpr int SPEED = 10;
};

