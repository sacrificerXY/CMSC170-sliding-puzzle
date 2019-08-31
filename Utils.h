#pragma once

#include <vector>

#include "Vec2.h"

#define for_loop_yx(max_x, max_y) for (int y = 0; y < max_y; y++) for (int x = 0; x < max_x; x++)

namespace utils
{
	//struct Vec2LoopYX
	//{
	//	int x = 0;
	//	int y = 0;

	//	Vec2LoopYX(int max_x, int max_y);
	//	bool not_finished() const;
	//	void operator++ (int);

	//private:
	//	int _max_x;
	//	int _max_y;
	//};

	std::vector<int> get_random_tile_order(int width, int height);
	std::vector<std::vector<int>> get_solved_tile_order(int width, int height);

	Vec2 get_zero_position(std::vector < std::vector<int>> vector_2d);


	template <typename V>
	typename V::value_type pop_front(V& v)
	{
		assert(!v.empty());
		typename V::value_type first = v.front();
		v.erase(v.begin());
		return first;
	}

}