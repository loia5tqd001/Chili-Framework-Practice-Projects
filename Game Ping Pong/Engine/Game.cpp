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
	CheckIfSwitchMode();

	Player2Move();
	Player1CheckAndMove();

	if (isWaiting) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			isWaiting = false;
		else
			return;
	}

	BotCheckAndMove();

	BallMove();
}

void Game::CheckIfSwitchMode()
{
	static bool releasedControl = true;
	if (wnd.kbd.KeyIsPressed(VK_CONTROL))
	{
		if (releasedControl)
		{
			_2players = !_2players;
			ball.Reset(true);
			player1.Reset();
			player2.Reset();
			isWaiting = true;
			releasedControl = false;
		}
	}
	else
	{
		releasedControl = true;
	}
}

void Game::Player2Move()
{
	int direction = 0;
	if (wnd.kbd.KeyIsPressed(VK_UP))
		direction |= MOVE_UP;
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
		direction |= MOVE_DOWN;
	player2.Move(direction);
}

void Game::Player1CheckAndMove()
{
	if (_2players)
	{
		int direction1 = 0;
		if (wnd.kbd.KeyIsPressed('W'))
			direction1 |= MOVE_UP;
		if (wnd.kbd.KeyIsPressed('S'))
			direction1 |= MOVE_DOWN;
		player1.Move(direction1);
	}
}

void Game::BotCheckAndMove()
{
	if (_2players)
		return;

	int direction1 = ball.AiDirection(player1.GetPaddle());
	player1.Move(direction1);
}

void Game::BallMove()
{
	SCORE_STATUS ballMove = ball.Move(player1.GetPaddle(), player2.GetPaddle());
	if (ballMove == P1_SCORE)
	{
		player1.Score();
		ball.Reset(P1_SCORE);
		isWaiting = true;
	}
	else if (ballMove == P2_SCORE)
	{
		player2.Score();
		ball.Reset(P2_SCORE);
		isWaiting = true;
	}
}


void Game::ComposeFrame()
{
	if (_2players)
		gfx.DrawDigit(2, 10, 10, 255, 0, 0);
	else
		gfx.DrawDigit(1, 10, 10, 255, 0, 0);

	ground.DrawGround(gfx);

	if (_2players)
		player1.Draw(gfx, Colors::White);
	else
		player1.Draw(gfx, Colors::Red);
	player2.Draw(gfx, Colors::White);

	ball.Draw(gfx);

}				  
