#include "Playground.h"





Playground & Playground::GetInstance()
{
	static Playground instance;
	return instance;
}

void Playground::DrawGround(Graphics & gfx) const
{
	// Horizontal lines
	gfx.DrawRectDim(X_MIN - 2, Y_MIN - 2, X_MAX - X_MIN + 4, 4, Colors::Blue);
	gfx.DrawRectDim(X_MIN - 2, Y_MAX - 2, X_MAX - X_MIN + 4, 4, Colors::Blue);

	// Vertical lines
	gfx.DrawRectDim(X_MIN - 2, Y_MIN - 2, 4, Y_MAX - Y_MIN + 4, Colors::Blue);
	gfx.DrawRectDim(X_MAX - 2, Y_MIN - 2, 4, Y_MAX - Y_MIN + 4, Colors::Blue);

	// Middle dashed vertical line
	for (int y = Y_MIN; y < Y_MAX; y += 10)
	{
		gfx.DrawRectDim((X_MIN + X_MAX) / 2 - 2, y + 2, 4, 6, Colors::Blue);
	}
}

int Playground::GetMiddleX() const
{
	return Graphics::ScreenWidth / 2;
}
