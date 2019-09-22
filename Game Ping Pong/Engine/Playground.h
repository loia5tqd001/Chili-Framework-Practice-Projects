#pragma once
#include "Graphics.h"

class Playground
{
private:
	Playground() = default;
	Playground(const Playground&) = default;
	Playground& operator=(const Playground&) = default;

public:
	static Playground& GetInstance();
	void DrawGround(Graphics& gfx) const;
	int GetMiddleX() const;

public:
	const int X_MIN = 150;
	const int X_MAX = Graphics::ScreenWidth - 150;
	const int Y_MIN = 100;
	const int Y_MAX = Graphics::ScreenHeight - 100;


};

