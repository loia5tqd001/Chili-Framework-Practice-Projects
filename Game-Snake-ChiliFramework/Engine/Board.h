#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include <assert.h>
#include "Random.h"

class Board
{
public:
	enum class Contents { EMPTY, FOOD, OBSTACLE, POISON };
	// Wall: OBSTACLE
	// Snake: EMPTY

private:
	static constexpr int MARGIN = 100;
	static constexpr int CELL_SIZE = 30;
	static constexpr int CELL_PADDING = 1;
	static constexpr int BORDER_THICKNESS = 3;
	static constexpr int WIDTH = (Graphics::ScreenWidth - 2 * MARGIN) / CELL_SIZE;
	static constexpr int HEIGHT = (Graphics::ScreenHeight - 2 * MARGIN) / CELL_SIZE;
	static constexpr Color BORDER_COLOR = Colors::Gray;
	static constexpr Color FOOD_COLOR = Colors::Red;
	static constexpr Color OBSTACLE_COLOR = Colors::Gray;
	static constexpr Color POISON_COLOR = Colors::MakeRGB(64, 8, 64);
	static constexpr int FOOD_RATIO = 100;
	static constexpr int POISON_RATIO = 10;
	static constexpr int MAX_N_OBSTACLE = (WIDTH * HEIGHT) / 20;


private:
	Board(Graphics& gfx, class Snake& snek);
	Board(const Board&) = delete;
	void Init(class Snake& snek);

	void DrawContents() const;
	void DrawScore(int score) const;
	void DrawBorder() const;

public:
	static Board& GetInstance(Graphics& gfx, class Snake& snek);
	int GetWidth() const;
	int GetHeight() const;
	void Reset(class Snake& snek);
	void DrawCell(const Vec2 &pos, Color c) const;
	void DrawBoard(int score) const;
	Contents ConsumeContent(const Vec2 &pos);
	void RespawnFood();
	void AddObstacle2x2(const Vec2& snekHead);
	
private:
	Graphics& gfx;
	Contents contents [HEIGHT * WIDTH];
	int nObstacles = 0;


};

