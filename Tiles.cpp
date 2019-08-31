#include "Tiles.h"

#include <cassert>
#include <utility>
using namespace std;

#include "Utils.h"

//Tiles::Tiles(int width, int height, std::vector<int> tile_order)
//	: _tiles(vector<vector<int>>(height, vector<int>(width)))
//	, _zero_pos(width-1, height-1)
//{
//	if (!tile_order.empty()) 
//		assert(tile_order.size() == width * height);
//
//	auto order = tile_order.begin();
//	for (int y = 0; y < height; y++)
//	for (int x = 0; x < width; x++)
//	{
//		if (!tile_order.empty())
//		{
//			_tiles[y][x] = *order;
//			if (_tiles[y][x] == 0)
//				_zero_pos = { x, y };
//			order++;
//		}
//		else
//		{
//			_tiles[y][x] = (y * width + x + 1);
//		}
//	}
//	if (tile_order.empty())
//		_tiles.back().back() = 0;
//}
//
//Tiles::Tiles(const Tiles* tiles, Vec2 move)
//	: _tiles(tiles->_tiles)
//	, _zero_pos(tiles->_zero_pos+move)
//{
//	std::swap(
//		this->_tiles[this->_zero_pos.y][this->_zero_pos.x],
//		this->_tiles[tiles->_zero_pos.y][tiles->_zero_pos.x]);
//}

Tiles Tiles::new_solved(int width, int height)
{
	vector<vector<int>> solved_order(height, vector<int>(width));
	for_loop_yx(width, height)
	{
		solved_order[y][x] = y * width + x + 1;
	}
	solved_order.back().back() = 0;
	return Tiles::new_from_order(solved_order);
}

Tiles Tiles::new_from_order(std::vector<std::vector<int>> tile_order)
{
	assert(!tile_order.empty() && !tile_order[0].empty() && "Tile order passed should be a non-empty 2D vector");
	
	// because c++ stores vectors in column-major order,
	int width = tile_order[0].size();
	int height = tile_order.size();

	Tiles tiles;
	tiles._tiles = tile_order;
	tiles._zero_pos = utils::get_zero_position(tile_order);
	return tiles;
}

Tiles Tiles::new_after_move(const Tiles& tiles, Vec2 move)
{
	Tiles new_tiles = tiles;	// create new copy
	new_tiles.do_move(move);	// do move on copy
	return new_tiles;
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

//Tiles Tiles::do_move2(Vec2 move) const
//{
//	return Tiles(this, move);
//}

Vec2 Tiles::get_zero_position() const
{
	return _zero_pos;
}


//int Tiles::operator() (int x, int y) const
//{
//	return _tiles[y][x];
//}
//
//int Tiles::operator()(Vec2 v) const
//{
//	return (*this)(v.x, v.y);
//}

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
