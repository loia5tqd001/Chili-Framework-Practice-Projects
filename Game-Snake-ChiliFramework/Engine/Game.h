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
#include "Snake.h"
#include "TimeFrame.h"
#include "SpriteCodex.h"
#include "SoundEffect.h"

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
	/********************************/
	/*  User Functions              */
	void ResetGame();
	bool CouldPlay();
	void GetKeyInput();
	void AddObstacle();
	void ProcessSnekMovement();
	
	void PlayNewGameSound();
	void StopNewGameSound();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;

	/********************************/
	Snake& snek = Snake::GetInstance();
	Board& board = Board::GetInstance(gfx, snek);

	Vec2 lastKeyPressed = {0, 0};
	int score = 0;
	float stalled_Time = 0.0f;
	float stallPeriod = 0.15f;
	static constexpr float minStallPeriod = 0.05f;

	bool isGameOver = false;
	bool isNewGame = true;

	Sound gameOverSound = Sound(L"Media\\gameover.wav");
	Sound newGameSound = Sound(L"Media\\Title.wav");
	SoundEffect eatFoodSound = SoundEffect({L"Media\\Eat.wav"});
	SoundEffect fartSound = SoundEffect({L"Media\\Fart.wav"});
	/*  User Variables              */
	/********************************/
};