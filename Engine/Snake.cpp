#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	segments[0].initHead(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		nSegments += 2;
	}
	for (int i = nSegments - 2; i < nSegments; i++)
	{
		segments[i].initBody();
		segments[i].Follow(segments[i - 1]);
	}
}

void Snake::Draw(Board & brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::colCheckAll(Location& in_loc)
{
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].getLoc().x == in_loc.x && segments[i].getLoc().y == in_loc.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Snake::colCheckHead(Location & in_loc)
{
	if (segments[0].getLoc().x == in_loc.x && segments[0].getLoc().y == in_loc.y)
	{
		Sleep(25);
		return true;
	}
	else
	{
		return false;
	}
}

void Snake::colTerm(bool& gameEnded)
{
	for (int i = 1; i < nSegments; i++)
	{
		Location segLoc = segments[i].getLoc();
		if (colCheckHead(segLoc))
		{
			gameEnded = true;
			snkvel = { 0, 0 };
		}
	}
	if (segments[0].getLoc().x > 38 || segments[0].getLoc().x < 1 || segments[0].getLoc().y > 28 || segments[0].getLoc().y < 1)
	{
		gameEnded = true;
		snkvel = { 0, 0 };
	}
}

void Snake::setLoc(Location in_loc)
{
	segments[0].setLoc(in_loc);
}

void Snake::Kill()
{
	nSegments = 1;
}



void Snake::Update(Keyboard & kbd)
{
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		if (snkvel.x != -1)
		{
			snkvel = { 1, 0 };
		}
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		if (snkvel.x != 1)
		{
			snkvel = { -1, 0 };
		}
	}
	if (kbd.KeyIsPressed(VK_DOWN))
	{
		if (snkvel.y != -1)
		{
			snkvel = { 0, 1 };
		}
	}
	if (kbd.KeyIsPressed(VK_UP))
	{
		if (snkvel.y != 1)
		{
			snkvel = { 0, -1 };
		}
	}
	MoveBy(snkvel);
}

void Snake::Segment::initHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::initBody()
{
	c = Snake::bodyColor;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

void Snake::Segment::setLoc(Location & in_loc)
{
	loc = in_loc;
}

Location Snake::Segment::getLoc()
{
	return loc;
}
