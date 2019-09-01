#include "Moveset.h"

#include <iostream>
using namespace std;

Moveset::Moveset(Vec2 size)
	: _moveset(vector<vector<vector<Vec2>>>(size.x, vector<vector<Vec2>>(size.y, vector<Vec2>())))
{
	for (Vec2Iterator pos(size); !pos.finished(); pos++)
	{
		if (pos.y != 0) _moveset[pos.x][pos.y].push_back(Vec2::UP);
		if (pos.y != size.y - 1) _moveset[pos.x][pos.y].push_back(Vec2::DOWN);
		if (pos.x != 0) _moveset[pos.x][pos.y].push_back(Vec2::LEFT);
		if (pos.x != size.x - 1) _moveset[pos.x][pos.y].push_back(Vec2::RIGHT);
		cout << pos.x << ',' << pos.y << ':' << _moveset[pos.x][pos.y] << '\n';
	}
}

std::ostream& operator<< (std::ostream& out, std::vector<Vec2> const& moveset)
{
	for (Vec2 v : moveset)
	{
		out << v;
	}
	return out;
}