#pragma once

#include <vector>
#include <ostream>

#include "Vec2.h"


struct Moveset
{
	const int width, height;
	Moveset(int width, int height);
	std::vector<Vec2> operator() (int x, int y) const
	{
		return moveset[x][y];
	}
	std::vector<Vec2> operator() (Vec2 v) const
	{
		return (*this)(v.x, v.y);
	}
private:
	std::vector<std::vector<std::vector<Vec2>>> moveset;
};

std::ostream& operator<< (std::ostream& out, std::vector<Vec2> const& moveset);

