#pragma once
#include "Paddle.h"
#include "Score.h"

class Player
{
private:
	Player(Paddle& paddle, Score& score);

public:
	static Player& GetPlayer1(const Playground& ground);
	static Player& GetPlayer2(const Playground& ground);
	void Draw(Graphics& gfx, Color paddleColor) const;
	const Paddle& GetPaddle() const;
	void Move(int direction);
	void Score();
	void Reset();

private:
	Paddle paddle;
	class Score score;
};

