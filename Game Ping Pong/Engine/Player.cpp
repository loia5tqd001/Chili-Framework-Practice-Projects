#include "Player.h"




Player::Player(Paddle & paddle, class Score & score) :
	paddle(paddle),
	score(score)
{}

Player & Player::GetPlayer1(const Playground & ground)
{
	static Player instance(Paddle::GetPaddle1(ground), Score::GetScorePlayer1(ground));
	return instance;
}

Player & Player::GetPlayer2(const Playground & ground)
{
	static Player instance(Paddle::GetPaddle2(ground), Score::GetScorePlayer2(ground));
	return instance;
}

void Player::Draw(Graphics & gfx, Color paddleColor) const
{
	paddle.Draw(gfx, paddleColor);
	score.Draw(gfx);
}

const Paddle & Player::GetPaddle() const
{
	return paddle;
}

void Player::Move(int direction)
{
	paddle.Move(direction);
}

void Player::Score()
{
	score.Increase();
}

void Player::Reset()
{
	score.Reset();
	paddle.Reset();
}
