#include "Utils.h"

#include <cassert>

#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>
#include <bitset>

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

	std::vector<int> get_random_tile_order(int length)
	{
		vector<int> tile_order(length);
		iota(tile_order.begin(), tile_order.end(), 1);
		tile_order.back() = 0;
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
			random_tiles[i / size.x][i % size.x] = tile_order[i];
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

	uint64_t adler_32(std::vector<std::vector<int>> tile_order)
	{
		int w = tile_order[0].size();
		int h = tile_order.size();
		int n = w * h;
		uint64_t sum = 0;
		cout << "bits --\n";
		for (int i = 0; i < n; i++)
			//for (int i = n - 1, t = 1; i >= 0; i--, t *= 10)
		{
			int x = i % w;
			int y = i / w;
			uint64_t num = tile_order[y][x];
			sum |= num << (i * 4);
			cout << bitset<64>(sum) << '\n';
		}
		return sum;


		//static constexpr int p = 65521;
		//uint32_t a = 1;
		//uint32_t b = 0;

		//int sum = 0;
		//for (int i = n - 1, t = 1; i >= 0; i--, t *= 10)
		//{
		//	int x = i % w;
		//	int y = i / w;
		//	sum += tile_order[y][x] * t;

		//}
		//return sum;
		//for (int i = 0; i < n; i++)
		//{
		//	int d = tile_order[y][x];
		//	a += d;
		//	b += d * (n - i);
		//}
		//b += n;

		//a %= p;
		//b %= p;
		//return (b << 16) + a;
	}

	void swap_bits(uint64_t& b, int i, int j, int n)
	{
		uint64_t x = ((b >> i) ^ (b >> j)) & ((1 << n) - 1);
		b = b ^ ((x << i) | (x << j));
	}

	int get_int(uint64_t bits, int pos)
	{
		int shift = 4 * pos;
		uint64_t mask = 0b1111;
		mask = mask << shift;
		//cout << bitset<64>(mask) << '\n';
		return (bits & mask) >> shift;
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
