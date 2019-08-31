#include "State.h"

#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;


std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>> const& tiles)
{
	for (auto row : tiles)
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


const State* State::create_solved(int width, int height)
{
	return new State(width, height);
}

const State* State::create_ordered(int width, int height, std::vector<int> tile_order)
{
	State* new_state = new State(width, height, tile_order);
	return new_state;
}

const State* State::do_move(Vec2 move) const
{
	return new State(this, move);
}

bool State::is_solved() const
{
	vector<int> solution(width * height);
	iota(solution.begin(), solution.end(), 0);
	rotate(solution.begin(), solution.begin()+1, solution.end());
	//for (int i : solution)
	//{
	//	cout << i << ' ';
	//}
	//cout << '\n';

	for (int y = 0; y < height; y++)
	for (int x = 0; x < width; x++)
	{
		//cout << "eq" << x << ',' << y << ' ' << tiles(x, y) << ' ' << solution[y * width + x] << '\n';
		if (tiles.at(x, y) != solution[y * width + x])
			return false;
	}
	return true;
}

bool State::is_solvable() const
{
	int inversions = 0;
	int w = width;

	auto indexToVec2 = [w](int i) {
		return Vec2(i % w, int(i / w));
	};

	for (int i = 0; i < width * height; i++) {
		// Check if a larger number exists after the current
		// place in the array, if so increment inversions.
		for (int j = i + 1; j < width * height; j++)
			if (tiles.at(indexToVec2(i)) > tiles.at(indexToVec2(j))) inversions++;

		// Determine if the distance of the blank space from the bottom 
		// right is even or odd, and increment inversions if it is odd.
		if (tiles.at(indexToVec2(i)) == 0 && i % 2 == 1) inversions++;
	}

	// If inversions is even, the puzzle is solvable.
	return (inversions % 2 == 0);
}

int State::get_heuristic() const
{
	vector<int> solution(width * height);
	iota(solution.begin(), solution.end(), 0);
	rotate(solution.begin(), solution.begin() + 1, solution.end());
	vector<Vec2> pos_map(width * height);

	for (int i : solution)
	{
		pos_map[solution[i]] = { i % width, i / width };
	}
	//for (int i : solution)
	//{
	//	cout << i << ' ';
	//}
	//cout << '\n';

	int dist = 0;

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			Vec2 delta = pos_map[tiles.at(x, y)] - Vec2(x, y);
			dist += abs(delta.x);
			dist += abs(delta.y);
		}
	return dist;
}

int State::get_total_cost() const
{
	return steps + get_heuristic();
}

State::State(int width, int height, std::vector<int> tile_order)
	: width(width)
	, height(height)
	//, zero_pos(width-1, height-1)
{ }

State::State(const State* state, Vec2 move)
	: width(state->width)
	, height(state->height)
	//, zero_pos(state->zer)
	//, tiles(state->tiles.do_move2(move))
	, prev_move(move)
	, steps(state->steps+1)
	, prev_state(state)
{
	/*std::swap(
		tiles(zero_pos.x, empty_tile_position.y),
		tiles(state->zero_pos.x, state->zero_pos.y)
	);*/

	//this->prev_state = state;
	//state->next_state = this;
}

GraphNode GraphNode::new_after_move(const Tiles& tiles, Vec2 move)
{
	return GraphNode();
}

GraphNode::GraphNode(const Tiles& tiles)
	: tiles(tiles)
{ }

GraphNode::GraphNode(GraphNode* parent, Vec2 move)
	: tiles(Tiles::new_after_move(parent->tiles, move))
	, parent(parent)
	, prev_move(move)
{
	parent->num_children++;
}
