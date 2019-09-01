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

bool Tiles::is_solved() const
{
	int width = _tiles[0].size();
	int height = _tiles.size();
	return _tiles == utils::get_solved_tile_order(width, height);
}

bool Tiles::is_solvable() const
{
	int inversions = 0;
	int width = _tiles[0].size();
	int height = _tiles.size();

	auto indexToVec2 = [width](int i) {
		return Vec2(
			i % width
			,
			int(i / width)
		);
	};

	for (int i = 0; i < width * height; i++) {
		if (at(indexToVec2(i)) == 0) continue;
		//cout << at(indexToVec2(i)) << ": ";
		// Check if a larger number exists after the current
		// place in the array, if so increment inversions.
		for (int j = i + 1; j < width * height; j++)
		{
			if (at(indexToVec2(j)) == 0) continue;
			if (at(indexToVec2(i)) > at(indexToVec2(j)))
			{
				inversions++;
				//cout << at(indexToVec2(j)) << ' ';
			}

		}
		//cout << '\n';

		//// Determine if the distance of the blank space from the bottom 
		//// right is even or odd, and increment inversions if it is odd.
		//if (at(indexToVec2(i)) == 0 && i % 2 == 1) inversions++;
	}
	//cout << "inv: " << inversions << '\n';
	bool width_odd = (width % 2 == 1);
	bool inversions_even = (inversions % 2 == 0);
	bool zero_on_odd_row_from_bottom = (((height - _zero_pos.y) % 1) == 1);

	if (width_odd && inversions_even) return true;
	if (!width_odd && (zero_on_odd_row_from_bottom == inversions_even)) return true;
	return false;

	// If inversions is even, the puzzle is solvable.
	return (inversions % 2 == 0);
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
