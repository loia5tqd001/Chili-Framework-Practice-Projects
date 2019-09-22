#pragma once
#include "GameObject.h"
#include "Dude.h"

#define GOAL_WIDTH 40
#define GOAL_HEIGHT 40

class Goal : public GameObject
{
private:
	Goal(int screenWidth, int screenHeight, const Dude& dude);
	void Draw(Graphics& gfx) const override;
	void ChangeColor();

public:
	static Goal& GetInstance(int screenWidth, int screenHeight, const Dude& dude);
	void Render(Graphics& gfx); 
	bool IsEaten(const Dude& dude) const;
	void Reposition(const Dude& dude);

private:
	int r = 100;
	bool isIncresing = false;
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
};

