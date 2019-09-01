#include "Tiles.h"

#include <cassert>
#include <iostream>
#include <utility>
using namespace std;

#include "Utils.h"
#include <numeric>

Tiles::Tiles(Vec2 size)
	//: Tiles{ utils::get_solved_tile_order(size) }
	: size{ size }
	, zero_pos{ size.x - 1, size.y - 1 }
	, _tiles{ utils::get_solved_tile_order(size) }
	, adler_32(utils::adler_32(_tiles))
{ }

Tiles::Tiles(std::vector<std::vector<int>> tile_order)
	: size{ tile_order[0].size() , tile_order.size() }
	, zero_pos { utils::get_zero_position(tile_order) }
	, _tiles{ tile_order }
	, adler_32(utils::adler_32(tile_order))
{ }

Tiles::Tiles(const Tiles& tiles, Vec2 move)
	: Tiles(tiles)
{
	do_move(move);
}

//void Tiles::calc_total_cost()
//{
//	//Vec2 size = tiles.size;
//	vector<int> solution(size.x * size.y);
//	iota(solution.begin(), solution.end(), 0);
//	rotate(solution.begin(), solution.begin() + 1, solution.end());
//	vector<Vec2> pos_map(solution.size());
//
//	for (int i : solution)
//	{
//		pos_map[solution[i]] = { i % size.x, i / size.x };
//	}
//	//for (int i : solution)
//	//{
//	//	cout << i << ' ';
//	//}
//	//cout << '\n';
//
//	int dist = 0;
//
//	for (Vec2Iterator pos(size); !pos.finished(); pos++)
//	{
//		Vec2 delta = pos_map[at(pos)] - pos;
//		dist += abs(delta.x);
//		dist += abs(delta.y);
//	}
//	total_cost = dist + depth;
//}

Tiles& Tiles::do_move(Vec2 move)
{
	Vec2 swap_pos = zero_pos + move;	// get position of tile to swap
	swap(at(zero_pos), at(swap_pos));	// do swap
	zero_pos = swap_pos;				// update new zero position
	adler_32 = utils::adler_32(_tiles);
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
	return zero_pos;
}

bool Tiles::is_solved() const
{
	Vec2 size(
		_tiles[0].size(),
		_tiles.size());
	return _tiles == utils::get_solved_tile_order(size);
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
		// Check if a larger number exists after the current
		// place in the array, if so increment inversions.
		for (int j = i + 1; j < width * height; j++)
		{
			if (at(indexToVec2(j)) == 0) continue;
			if (at(indexToVec2(i)) > at(indexToVec2(j)))
			{
				inversions++;
			}

		}
	}
	bool width_odd = (width % 2 == 1);
	bool inversions_even = (inversions % 2 == 0);
	bool zero_on_odd_row_from_bottom = (((height - zero_pos.y) % 1) == 1);

	if (width_odd && inversions_even) return true;
	if (!width_odd && (zero_on_odd_row_from_bottom == inversions_even)) return true;
	return false;
}

bool operator<(const Tiles& t1, const Tiles& t2)
{
	return t1.adler_32 < t2.adler_32;
}

bool operator==(const Tiles& t1, const Tiles& t2)
{
	//cout << "cmp: " << t1.adler_32 << ' ' << t2.adler_32 << '\n';
	//return t1._tiles == t2._tiles;
	return t1.adler_32 == t2.adler_32;
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
