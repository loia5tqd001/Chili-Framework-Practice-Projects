#include "Ball.h"



Ball & Ball::GetInstance(const Playground & ground)
{
	static Ball instance(ground);
	instance.Reset(P1_SCORE);
	return instance;
}

SCORE_STATUS Ball::Move(const Paddle& p1, const Paddle& p2)
{
	x += vx;
	y += vy;

	if (y < ground.Y_MIN)
	{
		y = ground.Y_MIN;
		vy = -vy;
	}
	else if (y + HEIGHT > ground.Y_MAX)
	{
		y = ground.Y_MAX - HEIGHT;
		vy = -vy;
	}

	if (Collide(p1))
	{
		x = p1.GetX() + p1.WIDTH;
		vx = -vx;
		vy += p1.Inertia() / 3;
	}
	else if (Collide(p2))
	{
		x = p2.GetX() - WIDTH;
		vx = -vx;
		vy += p2.Inertia() / 3;
	}

	const int THRESHOLD_SPEED = 13;
	if (vy > THRESHOLD_SPEED)
		vy = THRESHOLD_SPEED;
	else if (vy < -THRESHOLD_SPEED)
		vy = -THRESHOLD_SPEED;

	if (x < ground.X_MIN)
		return P2_SCORE;
	else if (x + WIDTH > ground.X_MAX)
		return P1_SCORE;
	else
		return NO_SCORE;
}

Ball::Ball(const Playground & ground) :
	ground(ground)
{}

bool Ball::Collide(const Paddle & p) const
{
	const int left0 = x;
	const int top0 = y;
	const int right0 = left0 + WIDTH;
	const int bottom0 = top0 + HEIGHT;

	const int left1 = p.GetX();
	const int top1 = p.GetY();
	const int right1 = left1 + p.WIDTH;
	const int bottom1 = top1 + p.HEIGHT;

	return
		right0 > left1 &&
		left0 < right1 &&
		bottom0 > top1 &&
		top0 < bottom1;
}



void Ball::Draw(Graphics & gfx) const
{
	#include "face (20x20).txt"
}

void Ball::Reset(SCORE_STATUS whoScored)
{
	x = ground.GetMiddleX() - WIDTH / 2;
	y = Random::Next(ground.Y_MIN + 50, ground.Y_MAX - HEIGHT - 50);

	vx = (whoScored == P2_SCORE) ? 10 : -10;

	do {
		vy = Random::Next(-3, 3);
	}
	while (vy == 0);
}

int Ball::AiDirection(const Paddle & p) const
{
	if (vx >= 0 || x > ground.GetMiddleX() + 100)
		return 0;

	static int direction;

	const float nFrameAnticipated = (abs(vy) > 8) ? 3.5 : 3;
	
	const int topball_in_future = y + nFrameAnticipated * vy;
	const int bottomball_in_future = topball_in_future + HEIGHT;

	const int topPaddle = p.GetY();
	const int bottomPaddle = topPaddle + p.HEIGHT;

	if (bottomball_in_future > bottomPaddle)
		direction = MOVE_DOWN;
	else if (topball_in_future < topPaddle)
		direction = MOVE_UP;

	return direction;
}
