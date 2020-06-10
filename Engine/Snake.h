#pragma once

#include "Board.h"
#include "Keyboard.h"

class Snake
{
private:
	class Segment
	{
	public:
		void initHead(const Location& in_loc);
		void initBody();
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		void setLoc(Location& in_loc);
		Location getLoc();
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	void Update(Keyboard& kbd);
	bool colCheckAll(Location& in_loc);
	bool colCheckHead(Location& in_loc);
	void colTerm(bool& gameEnded);
	void setLoc(Location in_loc);
	void Kill();
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 150;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
	Location snkvel = { 0, 0 };
};