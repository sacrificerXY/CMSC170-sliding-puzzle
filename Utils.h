#pragma once

#include <vector>

#include "Vec2.h"

namespace utils
{

	std::vector<int> get_random_tile_order(int width, int height);
	std::vector<int> get_random_tile_order(int length);
	std::vector<std::vector<int>> get_solved_tile_order(Vec2 size);
	std::vector<std::vector<int>> get_random_tile_order(Vec2 size);

	Vec2 get_2d_vector_size(std::vector<std::vector<int>> vector_2d);
	Vec2 get_zero_position(std::vector < std::vector<int>> vector_2d);

	uint64_t adler_32(std::vector<std::vector<int>>);
	void swap_bits(uint64_t& bits, int i, int j, int n);
	int get_int(uint64_t bits, int pos);


	template <typename V>
	typename V::value_type pop_front(V& v)
	{
		assert(!v.empty());
		typename V::value_type first = v.front();
		v.erase(v.begin());
		return first;
	}

	
}