#include "Tiles.h"

#include <cassert>
#include <iostream>
#include <utility>
using namespace std;

#include "Utils.h"

Tiles::Tiles(int width, int height)
	: Tiles{ utils::get_solved_tile_order(width, height) }
{ }

Tiles::Tiles(std::vector<std::vector<int>> tile_order)
	: _tiles{ tile_order }
	, _zero_pos{utils::get_zero_position(tile_order)}
{
	assert(!tile_order.empty() && !tile_order[0].empty() && "Tile order passed should be a non-empty 2D vector");
}

Tiles::Tiles(const Tiles& tiles, Vec2 move)
	: Tiles(tiles)
{
	do_move(move);
}

Tiles& Tiles::do_move(Vec2 move)
{
	Vec2 swap_pos = _zero_pos + move;	// get position of tile to swap
	swap(at(_zero_pos), at(swap_pos));	// do swap
	_zero_pos = swap_pos;				// update new zero position
	return *this;
}

int& Tiles::at(Vec2 v)
{
	return _tiles[v.y][v.x];
}

int& Tiles::at(int x, int y)
{
	return _tiles[y][x];
}

int Tiles::at(Vec2 v) const
{
	return _tiles[v.y][v.x];
}

int Tiles::at(int x, int y) const
{
	return _tiles[y][x];
}

Vec2 Tiles::get_zero_position() const
{
	return _zero_pos;
}

bool operator==(const Tiles& t1, const Tiles& t2)
{
	return t1._tiles == t2._tiles;
}

ostream& operator<<(ostream& out, Tiles const& tiles)
{
	for (auto row : tiles._tiles)
	{
		out << '|';
		for (auto tile : row)
		{
			out << ' ' << tile << ' ';
		}
		out << "|\n";
	}
	return out;
}
