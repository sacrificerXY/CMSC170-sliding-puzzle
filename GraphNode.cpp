#include "GraphNode.h"

#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

#include "Utils.h"
//
//bool State::is_solved() const
//{
//	vector<int> solution(width * height);
//	iota(solution.begin(), solution.end(), 0);
//	rotate(solution.begin(), solution.begin()+1, solution.end());
//	//for (int i : solution)
//	//{
//	//	cout << i << ' ';
//	//}
//	//cout << '\n';
//
//	for (int y = 0; y < height; y++)
//	for (int x = 0; x < width; x++)
//	{
//		//cout << "eq" << x << ',' << y << ' ' << tiles(x, y) << ' ' << solution[y * width + x] << '\n';
//		if (tiles.at(x, y) != solution[y * width + x])
//			return false;
//	}
//	return true;
//}

//bool State::is_solvable() const
//{
//	int inversions = 0;
//	int w = width;
//
//	auto indexToVec2 = [w](int i) {
//		return Vec2(i % w, int(i / w));
//	};
//
//	for (int i = 0; i < width * height; i++) {
//		// Check if a larger number exists after the current
//		// place in the array, if so increment inversions.
//		for (int j = i + 1; j < width * height; j++)
//			if (tiles.at(indexToVec2(i)) > tiles.at(indexToVec2(j))) inversions++;
//
//		// Determine if the distance of the blank space from the bottom 
//		// right is even or odd, and increment inversions if it is odd.
//		if (tiles.at(indexToVec2(i)) == 0 && i % 2 == 1) inversions++;
//	}
//
//	// If inversions is even, the puzzle is solvable.
//	return (inversions % 2 == 0);
//}

//int State::get_heuristic() const
//{
//	vector<int> solution(width * height);
//	iota(solution.begin(), solution.end(), 0);
//	rotate(solution.begin(), solution.begin() + 1, solution.end());
//	vector<Vec2> pos_map(width * height);
//
//	for (int i : solution)
//	{
//		pos_map[solution[i]] = { i % width, i / width };
//	}
//	//for (int i : solution)
//	//{
//	//	cout << i << ' ';
//	//}
//	//cout << '\n';
//
//	int dist = 0;
//
//	for (int y = 0; y < height; y++)
//		for (int x = 0; x < width; x++)
//		{
//			Vec2 delta = pos_map[tiles.at(x, y)] - Vec2(x, y);
//			dist += abs(delta.x);
//			dist += abs(delta.y);
//		}
//	return dist;
//}


GraphNode::GraphNode(const Tiles& tiles)
	: tiles{ tiles }
{ }

GraphNode::GraphNode(GraphNode* parent, Vec2 move)
	: tiles{ parent->tiles, move }
	, parent{ parent }
	, prev_move{ move }
	, depth { parent->depth + 1 }
{
	total_cost = get_cost(this);
	parent->_num_children++;
}


bool is_solved(const GraphNode* node)
{
	return node->tiles.is_solved();
}

bool is_solvable(const GraphNode* node)
{
	return node->tiles.is_solvable();
}

bool are_tiles_same(const GraphNode* node1, const GraphNode* node2)
{
	return node1->tiles == node2->tiles;
}

int get_cost(const GraphNode* node)
{
	Vec2 size = node->tiles.size;
	vector<int> solution(size.x * size.y);
	iota(solution.begin(), solution.end(), 0);
	rotate(solution.begin(), solution.begin() + 1, solution.end());
	vector<Vec2> pos_map(solution.size());

	for (int i : solution)
	{
		pos_map[solution[i]] = { i % size.x, i / size.x };
	}
	//for (int i : solution)
	//{
	//	cout << i << ' ';
	//}
	//cout << '\n';

	int dist = 0;

	for (Vec2Iterator pos(size); !pos.finished(); pos++)
		{
			Vec2 delta = pos_map[node->tiles.at(pos)] - pos;
			dist += abs(delta.x);
			dist += abs(delta.y);
		}
	return dist + node->depth;
	return 0;
}

bool greater_cost::operator()(const GraphNode* node1, const GraphNode* node2) const
{
	return get_cost(node1) > get_cost(node2);
}

bool lesser_cost::operator()(const GraphNode* node1, const GraphNode* node2) const
{
	return node1->total_cost < node2->total_cost;
}
