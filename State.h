#pragma once

#include <vector>
#include <ostream>

#include "Tiles.h"
#include "Move.h"

#include "Vec2.h"

struct GraphNode
{
	const Tiles tiles;
	const Vec2 prev_move;

	GraphNode* parent = nullptr;
	int num_children = 0;

	GraphNode(const Tiles& tiles);
	GraphNode(GraphNode* parent = nullptr, Vec2 move = Vec2());
};

