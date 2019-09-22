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
#include <thread>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
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
	if (CouldPlay() == false) return;
	GetKeyInput();
	AddObstacle();
	ProcessSnekMovement();
}

void Game::ResetGame()
{
	lastKeyPressed = {0, 0};
	stalled_Time = 0.0f;
	stallPeriod = 0.15f;
	score = 0;
	gameOverSound.StopAll();
	board.Reset(snek);
}

bool Game::CouldPlay()
{
	if (isNewGame == false && isGameOver == false)
		return true;

	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		isGameOver = false;
		isNewGame = false;
		ResetGame();
	}
	return false;	
}

void Game::GetKeyInput()
{
	if (wnd.kbd.KeyIsPressed(VK_UP))
		lastKeyPressed = Vec2(0, -1);
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		lastKeyPressed = Vec2(1, 0);
	else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		lastKeyPressed = Vec2(0, 1);
	else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		lastKeyPressed = Vec2(-1, 0);
}

void Game::AddObstacle()
{
	static float timePassed = 0;
	timePassed += TimeFrame::DeltaTime();
	if (timePassed > 5.0f)
	{
		timePassed -= 5.0f;
		board.AddObstacle2x2(snek.GetHead());
	}
}

void Game::ProcessSnekMovement()
{
	stalled_Time += TimeFrame::DeltaTime();

	if (stalled_Time < stallPeriod)
		return;
	else
	{
		stalled_Time -= stalled_Time;

		Vec2 afterProcessedDir = snek.ProcesssDirection(lastKeyPressed);
		switch (snek.Move(afterProcessedDir, board))
		{
			case Board::Contents::OBSTACLE:
				isGameOver = true;
				gameOverSound.Play();
				break;
			case Board::Contents::POISON:
				fartSound.Play(Random::GetRng(), 0.3f);
				stallPeriod = std::max(minStallPeriod, stallPeriod - 0.005f);
				if (snek.GetLength() < 1)
				{
					isGameOver = true;
					gameOverSound.Play();
				}
				break;
			case Board::Contents::FOOD:
				board.RespawnFood();
				eatFoodSound.Play(Random::GetRng(), 0.4f);
				score++;
				break;
		}
	}
}

void Game::PlayNewGameSound()
{
	static bool newGameSoundPlayed = false;
	if (!newGameSoundPlayed)
	{
		newGameSound.Play();
		newGameSoundPlayed = true;
	}
}

void Game::StopNewGameSound()
{
	newGameSound.StopAll();
}


void Game::ComposeFrame()
{
	if (isNewGame)
	{
		const int x = Graphics::ScreenWidth / 2 - 100;
		const int y = Graphics::ScreenHeight / 2 - 100;
		SpriteCodex::DrawTitle(x, y, gfx);
		PlayNewGameSound();
		return;
	}
	else 
	{
		StopNewGameSound();
	}

	board.DrawBoard(score);
	snek.Draw(board);

	if (isGameOver)
	{
		const int x = Graphics::ScreenWidth / 2 - 30;
		const int y = Graphics::ScreenHeight / 2 - 50;
		SpriteCodex::DrawGameOver(x, y, gfx);
	}
}
