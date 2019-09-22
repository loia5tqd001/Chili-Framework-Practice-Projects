#pragma once
#include "Playground.h"

class Score
{
private:
	Score(int x, int y);

public:
	void Draw(Graphics& gfx) const;
	void Increase();
	void Reset();
	static Score& GetScorePlayer1(const Playground& ground);
	static Score& GetScorePlayer2(const Playground& ground);

private:
	int value = 0;
	const int x;
	const int y;
};

