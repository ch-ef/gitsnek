#pragma once

#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include <random>

class Food
{
public:
	Food();
	void UpdateLoc(Snake& snk);
	void Draw(Board& brd);
	void colProc(Snake& snk);
	bool foodchk = false;
	Location getLoc();
private:
	void Place(Location in_loc);
	Location loc;
	Color c = (255, 255, 255);
	std::mt19937 rng;
};