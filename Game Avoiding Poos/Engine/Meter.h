#pragma once
#include "GameObject.h"

class Meter : public GameObject
{
private:
	Meter(int maxLevel);

public:
	static Meter& GetInstance(int screenWidth);
	void Draw(Graphics& gfx) const override;
	bool Increase();
	void Reset();

private:
	const int x = 10;
	const int y = 10;
	int level;
	static constexpr int DIMENSION = 20;
	const int MAX_LEVEL;
};

