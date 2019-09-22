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
#include "Time.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	TimeFrame::Mark();
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!isStarted)	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			isStarted = true;
		else
			return;
	}

	if (isWon) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			Reset();
		else
			return;
	}

	if (isGameOver && wnd.kbd.KeyIsPressed(VK_RETURN))
		Reset();

	int direction = 0;
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
		direction |= MOVE_LEFT;
	if (wnd.kbd.KeyIsPressed(VK_UP))
		direction |= MOVE_UP;
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		direction |= MOVE_RIGHT;
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
		direction |= MOVE_DOWN;

	dude.Move(direction, TimeFrame::DeltaTime());

	if (goal.IsEaten(dude))
	{
		if (meter.Increase() == false)
		{
			isWon = true;
			return;
		}
		poos.Aid(dude);
		goal.Reposition(dude);
	}

	if (poos.Move(dude) == false)
		isGameOver = true;
}

void Game::Reset()
{
	dude.Reset();
	poos.Reset(dude);
	goal.Reposition(dude);
	meter.Reset();
	isWon = false;
	isGameOver = false;
}

void Game::DrawTitle()
{
	const int x = (gfx.ScreenWidth - 150) / 2;
	const int y = (gfx.ScreenHeight - 175) / 2;
	#include "title (150x175).txt"
}

void Game::DrawGameOver()
{
	const int x = (gfx.ScreenWidth - 84) / 2;
	const int y = (gfx.ScreenHeight - 64) / 2;
	#include "game_over (84x64).txt"
}

void Game::ComposeFrame()
{
	if (!isStarted)
	{
		DrawTitle();
		return;
	}

	if (isGameOver)
	{
		DrawGameOver();
		return;
	}

	gfx.DrawRectDim(0, 39, gfx.ScreenWidth, 1, Colors::Blue);
	meter.Draw(gfx);
	poos.Draw(gfx);
	goal.Render(gfx);
	dude.Draw(gfx);
}
