#pragma once

#include <vector>
#include <ostream>

#include "Vec2.h"


struct Moveset
{
	Moveset(Vec2 size);

	std::vector<Vec2> at(Vec2 v) const
	{
		return _moveset[v.x][v.y];
	}
private:
	std::vector<std::vector<std::vector<Vec2>>> _moveset;
};

std::ostream& operator<< (std::ostream& out, std::vector<Vec2> const& moveset);

