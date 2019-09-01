#include "Utils.h"

#include <cassert>

#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

namespace utils
{
	std::vector<int> get_random_tile_order(int width, int height)
	{
		vector<int> tile_order(width * height);
		iota(tile_order.begin(), tile_order.end(), 1);
		//tile_order.back() = 0;
		shuffle(tile_order.begin(), tile_order.end(), default_random_engine(random_device()()));
		return tile_order;
	}

	std::vector<std::vector<int>> get_solved_tile_order(int width, int height)
	{
			vector<vector<int>> solved_order(height, vector<int>(width));
			for_loop_yx(width, height)
			{
				solved_order[y][x] = y * width + x + 1;
			}
			solved_order.back().back() = 0;
			return solved_order;
	}

	Vec2 get_zero_position(std::vector<std::vector<int>> vector_2d)
	{
		for (int y = 0; y < vector_2d.size(); y++)
		{
			for (int x = 0; x < vector_2d[y].size(); x++)
			{
				if (vector_2d[y][x] == 0)
				{
					return Vec2(x, y);
				}
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
