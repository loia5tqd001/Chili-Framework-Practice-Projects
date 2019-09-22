#include "Snake.h"

bool Snake::WillBangItself(const Vec2 & futureHead) const
{
	for (const Vec2& s : snek)
	{
		if (s == futureHead && s != snek.back())
		{
			return true;
		}
	}
	return false;
}

Snake & Snake::GetInstance()
{
	static Snake instance;
	return instance;
}

Board::Contents Snake::Move(const Vec2 & direction, Board& brd)
{
	assert(direction.LenSqr() == 1);

	lastDirection = direction;

	Vec2 futureHead = snek.front() + direction;
	if (WillBangItself(futureHead))
	{
		snek.push_front(futureHead);
		snek.pop_back();
		return Board::Contents::OBSTACLE;
	}

	snek.push_front(futureHead);
	Board::Contents contentConsumed = brd.ConsumeContent(futureHead);
	switch (contentConsumed)
	{
		case Board::Contents::POISON:
			snek.pop_back();

		case Board::Contents::EMPTY:
		case Board::Contents::OBSTACLE:
			snek.pop_back();

		case Board::Contents::FOOD:
			return contentConsumed;
	}
}

Vec2 Snake::ProcesssDirection(const Vec2 & preprocessedDir) const
{
	assert(preprocessedDir.LenSqr() == 1 || preprocessedDir.IsZero());

	if (preprocessedDir.IsZero()) // User doesn't press any key
		return lastDirection;
	else if (snek.size() <= 1) // does press key and snek only contains head
		return preprocessedDir;

	// If snek has something more than just head
	const Vec2 futureHead = snek.front() + preprocessedDir;
	const Vec2 currentNearHead = *(++snek.begin());
	const bool goBackward = (futureHead == currentNearHead);

	return goBackward ? lastDirection : preprocessedDir;
}

void Snake::Draw(const Board & brd) const
{
	if (snek.size() < 1)
		return;

	int i = -1;
	for (const auto& s: snek)
	{
		switch (i % 4)
		{
			case 0: brd.DrawCell(s, DARK_GREEN);	break;
			case 1: brd.DrawCell(s, MEDIUM_GREEN);	break;
			case 2: brd.DrawCell(s, LIGHT_GREEN);	break;
			case 3: brd.DrawCell(s, MEDIUM_GREEN);	break;		
		}

		i++;
	}

	brd.DrawCell(snek.front(), COLOR_HEAD);
}

Vec2 Snake::GetHead() const
{
	return snek.front();
}

int Snake::GetLength() const
{
	return snek.size();
}

Vec2 Snake::Init(int brdWidth, int brdHeight)
{
	snek.clear();

	snek.emplace_back(3, 0);
	snek.emplace_back(2, 0);
	snek.emplace_back(1, 0);
	snek.emplace_back(0, 0);
	lastDirection = {1, 0};

	return snek.front();
}
