#include "Move.h"

#include <iostream>
using namespace std;

Moveset::Moveset(int width, int height)
	: width(width)
	, height(height)
	, moveset(vector<vector<vector<Vec2>>>(width, vector<vector<Vec2>>(height, vector<Vec2>())))
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (y != 0) moveset[x][y].push_back(Vec2::UP);
			if (y != height - 1) moveset[x][y].push_back(Vec2::DOWN);
			if (x != 0) moveset[x][y].push_back(Vec2::LEFT);
			if (x != width - 1) moveset[x][y].push_back(Vec2::RIGHT);
			cout << x << ',' << y << ':' << moveset[x][y] << '\n';
		}
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