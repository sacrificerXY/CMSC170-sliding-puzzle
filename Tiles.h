#pragma once

#include <vector>
#include <ostream>

#include "Vec2.h"

struct Tiles
{
public: 
	// variables
	static Tiles new_solved(int width, int height);
	static Tiles new_from_order(std::vector<std::vector<int>> tile_order);
	static Tiles new_after_move(const Tiles& tiles, Vec2 move);

	Tiles& do_move(Vec2 move);
	int& at(Vec2 v);
	int& at(int x, int y);
	int at(Vec2 v) const;
	int at(int x, int y) const;
	//Tiles do_move2(Vec2 move) const;
	Vec2 get_zero_position() const;


	Tiles() = default;
private:
	//Tiles(int width, int height, std::vector<int> tile_order={});
	Vec2 _zero_pos;
	std::vector<std::vector<int>> _tiles;

	//Tiles(const Tiles* tiles, Vec2 move);

	friend std::ostream& operator<< (std::ostream& out, Tiles const& tiles);
	friend bool operator== (const Tiles& t1, const Tiles& t2);
};

bool operator== (const Tiles& t1, const Tiles& t2);
std::ostream& operator<< (std::ostream& out, Tiles const& tiles);

