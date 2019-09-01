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

	// Creates a node from the given tile
	GraphNode(const Tiles& tiles);

	// Creates a node which would be the result if the given parent node's tiles were to do the move
	GraphNode(GraphNode* parent, Vec2 move);
private:
	int _num_children = 0;

};

