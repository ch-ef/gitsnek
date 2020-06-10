#pragma once

struct Location
{
	void Add(const Location& delta)
	{
		x += delta.x;
		y += delta.y;
	}
	int x;
	int y;
};