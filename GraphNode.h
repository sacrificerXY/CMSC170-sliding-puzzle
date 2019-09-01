#pragma once

#include <vector>
#include <ostream>

#include "Tiles.h"
#include "Moveset.h"

#include "Vec2.h"

struct GraphNode
{
	const Tiles tiles;
	const Vec2 prev_move;
	GraphNode* parent = nullptr;
	int depth = 0;
	int total_cost = 0;

	// Creates a node from the given tile
	GraphNode(const Tiles& tiles);

	// Creates a node which would be the result if the given parent node's tiles were to do the move
	GraphNode(GraphNode* parent, Vec2 move);
private:
	int _num_children = 0;

};

bool is_solved(const GraphNode* node);
bool is_solvable(const GraphNode* node);

bool are_tiles_same(const GraphNode* node1, const GraphNode* node2);

int get_cost(const GraphNode* node1);

struct greater_cost
{
	bool operator() (const GraphNode* node1, const GraphNode* node2) const;
};

struct lesser_cost
{
	bool operator() (const GraphNode* node1, const GraphNode* node2) const;
};

