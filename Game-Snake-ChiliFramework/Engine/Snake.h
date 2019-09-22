#pragma once

#include <list>
#include "Board.h"

class Snake
{
private:
	Snake() = default;
	Snake(const Snake&) = delete;

	bool WillBangItself(const Vec2& futureHead) const;

public:
	static Snake& GetInstance();
	Vec2 Init(int brdWidth, int brdHeight);

	Vec2 ProcesssDirection(const Vec2 &preprocessedDir) const;
	Board::Contents Move(const Vec2& direction, Board& brd);
	void Draw(const Board& brd) const;
	Vec2 GetHead() const;
	int GetLength() const;

private:
	std::list<Vec2> snek;
	Vec2 lastDirection = {1, 0};
	// front---back
	// head----tail

	static constexpr Color COLOR_HEAD = Colors::MakeRGB(255, 171, 13);
	static constexpr Color DARK_GREEN = Colors::MakeRGB(8, 127, 57);
	static constexpr Color MEDIUM_GREEN = Colors::MakeRGB(0, 204, 83);
	static constexpr Color LIGHT_GREEN = Colors::MakeRGB(0, 255, 104);
};

