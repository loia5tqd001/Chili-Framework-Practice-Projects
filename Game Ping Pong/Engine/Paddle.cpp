#include "Paddle.h"

Paddle::Paddle(int x, int y, const Playground & ground) :
	x(x),
	y(y),
	ground(ground)
{}

int Paddle::GetX() const
{
	return x;
}

int Paddle::GetY() const
{
	return y;
}

int Paddle::Inertia() const
{
	return y - lastY;
}

Paddle & Paddle::GetPaddle1(const Playground& ground)
{
	static Paddle p1(ground.X_MIN + 95, (ground.Y_MAX - ground.Y_MIN) / 2, ground);
	return p1;
}

Paddle & Paddle::GetPaddle2(const Playground& ground)
{
	static Paddle p2(ground.X_MAX - 105, (ground.Y_MAX - ground.Y_MIN) / 2, ground);
	return p2;
}

void Paddle::Move(int direction)
{
	lastY = y;

	if (direction & MOVE_UP)
	{
		y -= SPEED;
	}
	if (direction & MOVE_DOWN)
	{
		y += SPEED;
	}

	if (y < ground.Y_MIN)
		y = ground.Y_MIN;
	else if (y + HEIGHT > ground.Y_MAX)
		y = ground.Y_MAX - HEIGHT;
}

void Paddle::Draw(Graphics & gfx, Color color) const
{
	gfx.DrawRectDim(x, y, WIDTH, HEIGHT, color);
}

void Paddle::Reset()
{
	y = (ground.Y_MAX - ground.Y_MIN) / 2;
}
