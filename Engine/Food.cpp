#include "Food.h"
#include "Snake.h"
#include <random>

Food::Food()
	:
	rng(std::random_device()())
{}

void Food::UpdateLoc(Snake& snk)
{
	while (!foodchk)
	{
		std::uniform_int_distribution<int> locxDist(1, 38);
		std::uniform_int_distribution<int> locyDist(1, 28);
		Location temp_loc = { locxDist(rng), locyDist(rng) };
		foodchk = true;
		if (snk.colCheckAll(temp_loc))
		{
			foodchk = false;
		}
		else
		{
			loc = temp_loc;
		}
	}
}

void Food::Place(Location in_loc)
{
	loc = in_loc;
}

void Food::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

void Food::colProc(Snake & snk)
{
	if (snk.colCheckHead(loc))
	{
		foodchk = false;
		snk.Grow();
	}
}

Location Food::getLoc()
{
	return loc;
}
