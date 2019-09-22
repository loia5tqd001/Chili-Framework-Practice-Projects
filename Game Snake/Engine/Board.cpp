#include "Board.h"
#include "Snake.h"



Board::Board(Graphics & gfx, class Snake& snek) :
	gfx(gfx)
{
	Init(snek);
}


void Board::DrawBorder() const
{
	const int leftBrd = MARGIN;
	const int topBrd = MARGIN;
	const int rightBrd = Graphics::ScreenWidth - MARGIN;
	const int bottomBrd = Graphics::ScreenHeight - MARGIN;

	// left
	gfx.DrawRectDim(
		leftBrd - BORDER_THICKNESS,
		topBrd,
		BORDER_THICKNESS,
		CELL_SIZE * HEIGHT,
		BORDER_COLOR);

	// top
	gfx.DrawRectDim(
		leftBrd - BORDER_THICKNESS,
		topBrd - BORDER_THICKNESS,
		CELL_SIZE * WIDTH + 2 * BORDER_THICKNESS,
		BORDER_THICKNESS,
		BORDER_COLOR);

	// right
	gfx.DrawRectDim(
		rightBrd,
		topBrd,
		BORDER_THICKNESS,
		CELL_SIZE * HEIGHT,
		BORDER_COLOR);

	// bottom
	gfx.DrawRectDim(
		leftBrd - BORDER_THICKNESS,
		bottomBrd,
		2 * BORDER_THICKNESS + CELL_SIZE * WIDTH,
		BORDER_THICKNESS,
		BORDER_COLOR);
}



void Board::DrawContents() const
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			Vec2 pos(x, y);
			switch (contents[y * WIDTH + x])
			{
				case Contents::FOOD:
					DrawCell(pos, FOOD_COLOR);
					break;
				case Contents::OBSTACLE:
					DrawCell(pos, OBSTACLE_COLOR);
					break;
				case Contents::POISON:
					DrawCell(pos, POISON_COLOR);
					break;
			}
		}
	}
}

void Board::DrawScore(int score) const
{
	int x = (2 * Graphics::ScreenWidth) / 3;
	const int y = 50;

	std::list<char> digits;
	do
	{
		digits.emplace_front(score % 10);
		score /= 10;
	}
	while (score > 0);

	for (char d : digits)
	{
		gfx.DrawDigit(d, x, y, 255, 0, 0);
		x += 30;
	}
}

void Board::DrawCell(const Vec2 & pos, Color c) const
{
	assert(pos.x >= -1 && pos.x < WIDTH + 1
		&& pos.y >= -1 && pos.y < HEIGHT + 1);

	const int x = MARGIN + pos.x * CELL_SIZE + CELL_PADDING;
	const int y = MARGIN + pos.y * CELL_SIZE + CELL_PADDING;
	const int wh = CELL_SIZE - 2 * CELL_PADDING;
	gfx.DrawRectDim(x, y, wh, wh, c);

	gfx.PutPixel(x, y, Colors::Black);
	gfx.PutPixel(x + wh - 1, y, Colors::Black);
	gfx.PutPixel(x, y + wh - 1, Colors::Black);
	gfx.PutPixel(x + wh - 1, y + wh - 1, Colors::Black);
}

void Board::Init(class Snake& snek)
{
	Vec2 snekHead = snek.Init(WIDTH, HEIGHT);
	const int xHead = snekHead.x;
	const int yHead = snekHead.y;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (x - xHead < 5 && y - yHead < 2)
			{
				contents[y * WIDTH + x] = Contents::EMPTY;
			}
			else if (Random::Next(1, FOOD_RATIO) == 1)
			{
				contents[y * WIDTH + x] = Contents::FOOD;
			}
			else if (Random::Next(1, POISON_RATIO) == 1)
			{
				contents[y * WIDTH + x] = Contents::POISON;
			}
			else
			{
				contents[y * WIDTH + x] = Contents::EMPTY;
			}
		}
	}
}

void Board::Reset(Snake & snek)
{
	nObstacles = 0;
	Init(snek);
}


int Board::GetWidth() const
{
	return WIDTH;
}

int Board::GetHeight() const
{
	return HEIGHT;
}

Board::Contents Board::ConsumeContent(const Vec2 & pos)
{
	if (pos.x < 0 || pos.x >= WIDTH || pos.y < 0 || pos.y >= HEIGHT)
		return Contents::OBSTACLE;

	Contents contentComsumed = contents[pos.y * WIDTH + pos.x];
	contents[pos.y * WIDTH + pos.x] = Contents::EMPTY;
	return contentComsumed;
}

void Board::RespawnFood()
{
	// TODO: Check if there is no rooms available for Foods

	int x, y;
	Contents content;
	do
	{
		x = Random::Next(0, WIDTH - 1);
		y = Random::Next(0, HEIGHT - 1);
		content = contents[y * WIDTH + x];
	}
	while (content != Contents::EMPTY && content != Contents::POISON);

	contents[y * WIDTH + x] = Contents::FOOD;
}


void Board::AddObstacle2x2(const Vec2& snekHead)
{
	if (nObstacles < MAX_N_OBSTACLE)
	{
		// TODO: Check if there is no rooms available for obstacles

		int x, y;
		bool condition;
		do
		{
			x = Random::Next(0, WIDTH - 2);
			y = Random::Next(0, HEIGHT - 2);

			// condition: square 2x2 is not food and position is 3 cells is away from snekHead
			condition = ( contents[y * WIDTH + x] != Contents::FOOD )
				&& ( contents[y * WIDTH + x+1] != Contents::FOOD )
				&& ( contents[(y + 1) * WIDTH + x] != Contents::FOOD )
				&& ( contents[(y + 1) * WIDTH + x+1] != Contents::FOOD )
				&& ( abs(x - snekHead.x) > 3 && abs(y - snekHead.y) > 3 );
		}
		while (!condition);

		// Random obstacles for square 2x2 have occupied
		for (int yy = y; yy <= y + 1; yy++)
		{
			for (int xx = x; xx <= x + 1; xx++)
			{
				if (Random::Next(0, 1) == 1)
				{
					contents[yy * WIDTH + xx] = Contents::OBSTACLE;
					nObstacles++;
				}
			}
		}
	}
}

void Board::DrawBoard(int score) const
{
	DrawBorder();
	DrawContents();
	DrawScore(score);
}

Board & Board::GetInstance(Graphics & gfx, class Snake& snek)
{
	static Board instance(gfx, snek);
	return instance;
}
