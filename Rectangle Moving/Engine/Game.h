/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

enum State {solid, outline};

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();

private:
	void DrawInstructionBar();
	void DrawStatusBar();
	void DrawBox(int x, int y, int width, int height, int r = 255, int g = 255, int b = 255);
	void DrawCharacter(int x, int y, char c);
	void Draw3DigitsNumber(int x, int y, int number);

	void DrawMinBox();
	void DrawShape();
	void DrawMaxBox();

	void ProcessBoostSpeed(bool isControlPressing);
	void ProcessChangeState(bool isSpacePressing);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	const int MINWIDTH = 50;
	const int MINHEIGHT = 50;
	const int MAXWIDTH = 400;
	const int MAXHEIGHT = 300;

	int x = (gfx.ScreenWidth - MAXWIDTH) / 2;
	int y = (gfx.ScreenHeight - MAXHEIGHT) / 2;
	int width = MINWIDTH;
	int height = MINHEIGHT;
	int speed = 2;
	State state = outline;
	float time_count_down = 10.0f;
	/********************************/
};