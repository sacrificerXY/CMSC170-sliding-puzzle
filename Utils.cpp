#include "Utils.h"

#include <cassert>

#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>

using namespace std;

namespace utils
{
	std::vector<int> get_random_tile_order(int width, int height)
	{
		vector<int> tile_order(width * height);
		iota(tile_order.begin(), tile_order.end(), 1);
		shuffle(tile_order.begin(), tile_order.end(), default_random_engine(random_device()()));
		return tile_order;
	}

	std::vector<std::vector<int>> get_solved_tile_order(Vec2 size)
	{
			vector<vector<int>> solved_order(size.y, vector<int>(size.x));

			for (Vec2Iterator pos(size); !pos.finished(); pos++)
			{
				solved_order[pos.y][pos.x] = pos.y * size.x + pos.x + 1;
			}
			solved_order.back().back() = 0;
			return solved_order;
	}

	std::vector<std::vector<int>> get_random_tile_order(Vec2 size)
	{
		vector<int> tile_order(size.x * size.y);
		iota(tile_order.begin(), tile_order.end(), 1);
		tile_order.back() = 0;
		shuffle(tile_order.begin(), tile_order.end(), default_random_engine(random_device()()));
		vector<vector<int>> random_tiles(size.y, vector<int>(size.x));
		for (int i = 0; i < tile_order.size(); i++)
		{
			random_tiles[i / size.y][i % size.y] = tile_order[i];
		}
		return random_tiles;
	}

	Vec2 get_2d_vector_size(std::vector<std::vector<int>> vector_2d)
	{
		if (vector_2d.empty() || vector_2d[0].empty()) return Vec2(0, 0);
		return Vec2(vector_2d[0].size(), vector_2d.size());
	}

	Vec2 get_zero_position(std::vector<std::vector<int>> vector_2d)
	{
		Vec2 size = get_2d_vector_size(vector_2d);
		for (Vec2Iterator pos(size); !pos.finished(); pos++)
		{
			if (vector_2d[pos.y][pos.x] == 0)
			{
				cout << "zero: " << pos.x << ',' << pos.y << '\n';
				return pos;
			}
		}
		// If the part below is executed, something is wrong
		assert(false && "vector doesn't contain a zero");
		return Vec2(-1, -1);
	}



	//Vec2LoopYX::Vec2LoopYX(int max_x, int max_y)
	//	: _max_x(max_x), _max_y(max_y)
	//{ }

	//bool Vec2LoopYX::not_finished() const
	//{
	//	return x < _max_x && y < _max_y;
	//}

	//void Vec2LoopYX::operator++(int)
	//{
	//	++x;
	//	if (x == _max_x)
	//	{
	//		x = 0;
	//		++y;
	//	}

	//}

}
