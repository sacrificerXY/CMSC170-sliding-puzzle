#pragma once

#include <vector>
#include <ostream>

#include "Vec2.h"


struct Moveset
{
	Moveset(int width, int height);

	std::vector<Vec2> at(int x, int y) const
	{
		return _moveset[x][y];
	}
	std::vector<Vec2> at(Vec2 v) const
	{
		return _moveset[v.x][v.y];
	}
private:
	std::vector<std::vector<std::vector<Vec2>>> _moveset;
};

std::ostream& operator<< (std::ostream& out, std::vector<Vec2> const& moveset);

