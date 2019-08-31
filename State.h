#pragma once

#include <vector>
#include <ostream>

#include "Tiles.h"
#include "Move.h"

#include "Vec2.h"




struct State
{
	int width, height;

	Tiles tiles;
	//Vec2 zero_pos;

	Vec2 prev_move;
	mutable const State* prev_state = nullptr;
	//mutable const State* next_state = nullptr;
	int steps = 0;

	static const State* create_solved(int width, int height);
	static const State* create_ordered(int width, int height, std::vector<int> tile_order = {});
	const State* do_move(Vec2 move) const;

	bool is_solved() const;
	bool is_solvable() const;
	int get_heuristic() const;
	int get_total_cost() const;

	// constructors
	State() = default;
	State(int width, int height, std::vector<int> tile_order = {});
	State(const State* state, Vec2 move);
};

struct GraphNode
{
	//const State* state = nullptr;
	const Tiles tiles;
	const Vec2 prev_move;

	GraphNode* parent = nullptr;
	int num_children = 0;

	static GraphNode new_after_move(const Tiles& tiles, Vec2 move);
//private:
	GraphNode(const Tiles& tiles);
	GraphNode(GraphNode* parent = nullptr, Vec2 move = Vec2());
};


std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>> const& tiles);
