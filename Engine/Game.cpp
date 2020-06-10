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
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	snk({ 1, 1 }),
	rng(std::random_device()())
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameStarted = true;
		}
	}
	if (gameStarted && !gameEnded)
	{
		snk.Update(wnd.kbd);
		snk.colTerm(gameEnded);
		food.UpdateLoc(snk);
		food.colProc(snk);
		Sleep(75);
	}
	if (gameEnded)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameEnded = false;
			snk.Kill();
			snk.setLoc({ 1,1 });
			food.foodchk = false;
		}
	}
}

void Game::ComposeFrame()
{
	if (!gameStarted)
	{
		sprt.DrawTitle(0, 0, gfx);
	}
	else if (gameStarted)
	{
		for (int y = 0; y < brd.getHeight(); y++)
		{
			for (int x = 0; x < brd.getWidth(); x++)
			{
				Location loc = { x, y };
				if (loc.x == 0 || loc.x == 39 || loc.y == 0 || loc.y == 29)
				{
					Color c(255, 255, 255);
					brd.DrawCell(loc, c);
				}
			}
		}
		snk.Draw(brd);
		food.Draw(brd);
		if (gameEnded)
		{
			sprt.DrawGameOver(358, 268, gfx);
		}
	}
}
