#pragma once
#include "Graphics.h"
#include "Random.h"


class GameObject
{
public:
	void virtual Draw(Graphics&) const = 0;
	GameObject(int x, int y);
	GameObject() = default;

protected:
	int x, y;
};



