/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "Timer.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	Timer timer(time_count_down);

	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	// boost speed for only 10 seconds
	// collide is checked when moving but not when resizing
	ProcessChangeState(wnd.kbd.KeyIsPressed(VK_SPACE));
	ProcessBoostSpeed(wnd.kbd.KeyIsPressed(VK_CONTROL));

	static const int resize = 5;
	if (wnd.kbd.KeyIsPressed('A') && width > MINWIDTH)
		width -= resize;
	if (wnd.kbd.KeyIsPressed('W') && height > MINHEIGHT)
		height -= resize;
	if (wnd.kbd.KeyIsPressed('D') && width < MAXWIDTH)
		width += resize;
	if (wnd.kbd.KeyIsPressed('S') && height < MAXHEIGHT)
		height += resize;

	if (wnd.kbd.KeyIsPressed(VK_LEFT))
		x -= speed;
	if (wnd.kbd.KeyIsPressed(VK_UP))
		y -= speed;
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		x += speed;
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
		y += speed;

	if (x < 0) 
		x = 0;
	if (y < 50) 
		y = 50;
	if (x + width >= gfx.ScreenWidth)
		x = gfx.ScreenWidth - width;
	if (y + height >= gfx.ScreenHeight - 50)
		y = gfx.ScreenHeight - height - 50;

}

void Game::DrawInstructionBar()
{
	int x = 0, y = 0;
	#include "BitmapScripts/instruction-bar (1400x50).txt"
}

void Game::DrawStatusBar()
{
	// 100  ^Current Speed:(320)^  |speed-25| space  ^Current Size:(300)^  |width-75|  ^x(25)^  |height-75| space  ^State(130)^  |state-175|
	// |var-number| => variables
	// ^label(number)^ => fixed labels
	// space => a whitespace
	// number => indentation

	const int barHeight = 50;
	const int y = gfx.ScreenHeight - barHeight;
	const int space = 50;
	int x = 0;
	DrawBox(x, y, gfx.ScreenWidth, barHeight); // Fill status bar with white background

	x = 100;
	#include "BitmapScripts/current_speed (320x50).txt"

	x += 320;
	DrawCharacter(x, y, speed + '0');

	x += 25 + space;
	#include "BitmapScripts/current_size (300x50).txt"

	x += 300;
	Draw3DigitsNumber(x, y, width);

	x += 75;
	#include "BitmapScripts/x (25x50).txt"

	x += 25;
	Draw3DigitsNumber(x, y, height);

	x += 75 + space;
	#include "BitmapScripts/state (130x50).txt"

	x += 130;
	if (state == solid) {
		#include "BitmapScripts/solid (110x50).txt"
	}
	else {
		#include "BitmapScripts/outline (165x50).txt"
	}
}

void Game::DrawBox(int xPos, int yPos, int width, int height, int r, int g, int b)
{
	for (int y = yPos; y < yPos + height; y++)
		for (int x = xPos; x < xPos + width; x++)
			gfx.PutPixel(x, y, r, g, b);
}

void Game::DrawCharacter(int x, int y, char c)
{
	switch (c) {
		case '0':
			#include "BitmapScripts/0 (25x50).txt"
			break;
		case '1':
			#include "BitmapScripts/1 (25x50).txt"
			break;
		case '2':
			#include "BitmapScripts/2 (25x50).txt"
			break;
		case '3':
			#include "BitmapScripts/3 (25x50).txt"
			break;
		case '4':
			#include "BitmapScripts/4 (25x50).txt"
			break;
		case '5':
			#include "BitmapScripts/5 (25x50).txt"
			break;
		case '6':
			#include "BitmapScripts/6 (25x50).txt"
			break;
		case '7':
			#include "BitmapScripts/7 (25x50).txt"
			break;
		case '8':
			#include "BitmapScripts/8 (25x50).txt"
			break;
		case '9':
			#include "BitmapScripts/9 (25x50).txt"
			break;
		default:
			#include "BitmapScripts/x (25x50).txt"
			break;

	}
}

void Game::Draw3DigitsNumber(int x, int y, int number)
{
	if (number > 999) return;

	const int units = number % 10;
	const int tens = (number / 10) % 10;
	const int hundreds = number / 100;

	DrawCharacter(x, y, hundreds + '0');
	DrawCharacter(x + 25, y, tens + '0');
	DrawCharacter(x + 50, y, units + '0');
}

void Game::DrawMinBox()
{
	DrawBox(x, y, MINWIDTH, MINHEIGHT, 255, 0, 0);
}

void Game::DrawShape()
{
	if (state == solid)
		DrawBox(x, y, width, height, 255, 255, 255);
	else
	{
		for (int x = this->x; x < this->x + width; x++)
		{
			gfx.PutPixel(x, y, 255, 255, 255);
			gfx.PutPixel(x, y + height - 1, 255, 255, 255);
		}
		for (int y = this->y; y < this->y + height; y++)
		{
			gfx.PutPixel(x, y, 255, 255, 255);
			gfx.PutPixel(x + width - 1, y, 255, 255, 255);
		}
		for (int i = MINWIDTH + 5; i < width + height; i+=20)
		{
			for (int j = 0; j < i && j < width; j++)
			{
				if (i - j < height)
					gfx.PutPixel(x + j, y + i - j, 255, 255, 255);
			}

		}

	}
}

void Game::DrawMaxBox()
{
	for (int x = this->x; x < this->x + width; x++)
		gfx.PutPixel(x, y, 255, 255, 255);

	for (int y = this->y; y < this->y + height; y++)
		gfx.PutPixel(x, y, 255, 255, 255);

	for (int i = width; i < MAXWIDTH && x + i < gfx.ScreenWidth; i++)
		gfx.PutPixel(x + i, y, 255, 255, 255);

	for (int i = height; i < MAXHEIGHT && y + i < gfx.ScreenHeight; i++)
		gfx.PutPixel(x, y + i, 255, 255, 255);

	if (x + MAXWIDTH < gfx.ScreenWidth)
		for (int i = 0; i < MAXHEIGHT && y + i < gfx.ScreenHeight - 50; i++)
			gfx.PutPixel(x + MAXWIDTH - 1, y + i, 255, 255, 255);

	if (y + MAXHEIGHT < gfx.ScreenHeight)
		for (int i = 0; i < MAXWIDTH && x + i < gfx.ScreenWidth; i++)
			gfx.PutPixel(x + i, y + MAXHEIGHT - 1, 255, 255, 255);
}

void Game::ProcessBoostSpeed(bool isControlPressing)
{
	static int controlReleased = true;

	if (time_count_down < 0)
	{
		time_count_down = 10.0f;
		speed = 2;
	}

	if (isControlPressing) 	{
		if (controlReleased) 
		{
			speed = 5;
			time_count_down = 10.0f;
		}
	}

	controlReleased = !isControlPressing;
}

void Game::ProcessChangeState(bool isSpacePressing)
{
	static int spaceReleased = true;

	if (isSpacePressing) {
		if (spaceReleased)
		{
			state = (state == solid) ? outline : solid;
			spaceReleased = false;
		}
	}
	else {
		spaceReleased = true;
	}
}

void Game::ComposeFrame()
{
	DrawMaxBox();
	DrawShape();
	DrawMinBox();
	DrawInstructionBar();
	DrawStatusBar();
}
