#pragma once

#include <vector>
#include <ostream>

#include "Vec2.h"


struct Tiles
{
public:
	const Vec2 size;
	Vec2 zero_pos;

	// Swaps the zero tile in the direction specified by the move vector
	Tiles& do_move(Vec2 move);

	// Returns the x,y position of the zero tile / empty tile
	Vec2 get_zero_position() const;

	bool is_solved() const;
	bool is_solvable() const;

	// Access tiles by x,y coordinates
	int& at(int x, int y);
	int at(int x, int y) const;
	int& at(Vec2 v);
	int at(Vec2 v) const;


	// Creates tiles in a solved state
	Tiles(Vec2 size);

	// Creates tiles with a given tile order
	Tiles(std::vector<std::vector<int>> tile_order);

	// Creates tiles which would be the result if passed in tiles were to do the move
	Tiles(const Tiles& tiles, Vec2 move);

private:
	std::vector<std::vector<int>> _tiles;
	int32_t adler_32;
	//int total_cost;

	//void calc_total_cost();

	friend std::ostream& operator<< (std::ostream& out, Tiles const& tiles);
	friend bool operator< (const Tiles& t1, const Tiles& t2);
	friend bool operator== (const Tiles& t1, const Tiles& t2);
};

bool is_solved(const Tiles& tiles);
bool is_solvable(const Tiles& tiles);

bool operator< (const Tiles& t1, const Tiles& t2);
bool operator== (const Tiles& t1, const Tiles& t2);
std::ostream& operator<< (std::ostream& out, Tiles const& tiles);

