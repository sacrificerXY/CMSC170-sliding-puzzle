#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <array>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <iomanip>
#include <queue>
#include <set>

#include "Moveset.h"
#include "Tiles.h"
#include "GraphNode.h"
#include "Utils.h"

using namespace std;

struct lesser_tiles
{
	bool operator()(const GraphNode* n1, const GraphNode* n2) const
	{
		return n1->tiles < n2->tiles;
	}
};

int main()
{
	//Tiles tiles{ {{1, 2}, {3, 0}} };
	//GraphNode* rr = new GraphNode(utils::get_random_tile_order(size));
	//GraphNode* rr2 = new GraphNode(rr, Vec2::UP);
	////tiles = Tiles{ tiles, Vec2::LEFT };
	////tiles.do_move(Vec2::UP)
	////	.do_move(Vec2::LEFT)
	////	.do_move(Vec2::DOWN);
	//cout << rr->tiles << '\n';
	//cout << rr2->tiles << '\n';
	//cout << "tiles: " << tiles;
	//cout << "zero: " << tiles.get_zero_position();

	//Vec2 a, b;
	//a < b;

	//vector<int> wiki = {
	//	{1,2
	//};

	//auto adler = utils::adler_32(utils::get_solved_tile_order(size));
	//cout << std::hex << adler << '\n';
	//return 0;

	//auto zz = new GraphNode(utils::get_solved_tile_order(size));
	//auto yy = new GraphNode(zz, Vec2(0, -1));
	//cout << std::boolalpha << are_tiles_same(zz, yy) << '\n';
	//return 0;


	Vec2 size(4, 4);
	GraphNode* root;
	do
	{
		root = new GraphNode(utils::get_random_tile_order(size));
	} while (!is_solvable(root));
	//root = new GraphNode(Tiles({ {0,5,3,2,1},{9,4,8,7,6} }));
	//root = new GraphNode(Tiles({ {6,4,7},{8,5,0},{3,2,1} }));
	//size = Vec2(3, 3);
	cout << std::boolalpha << is_solvable(root) << '\n';
	cout << "Size: " << sizeof(GraphNode) << '\n';


	Moveset moveset(size);
	vector<int> va(10000, 0);
	vector<vector<int>> vb(100, vector<int>(100, 0));
	cout << "Size: " << sizeof(va) << '\n';
	cout << "Size: " << sizeof(vb) << '\n';
	//return 0;

	//root = new GraphNode(utils::get_solved_tile_order(size));
	//root = new GraphNode(root, moveset.at(root->tiles.get_zero_position())[0]);

	cout << "ROOT\n";
	cout << root->tiles << '\n';

	set<GraphNode*, lesser_cost> open_nodes;
	//set<Grap
	//auto lesser_tiles = [](auto n1, auto n2) {return n1->tiles < n2->tiles; };
	//vector<GraphNode*> open_
	set<GraphNode*, lesser_tiles> open_set;
	//open_nodes.reserve(20000);
	open_nodes.insert(root);
	open_set.insert(root);

	GraphNode* current = nullptr;
	int i = 0;
	int max_iter = 100000;

	float total_depth = 0;
	int num_closed = 0;
	int max_depth = 0;
	sf::Clock clock;
	while (!open_nodes.empty() && i < max_iter)
	{
		current = utils::pop_front(open_nodes);
		//total_depth += current->depth;
		//num_closed++;
		max_depth = max(max_depth, current->depth);
		//cout << "max: " << max_depth << "   avg: " << (total_depth / num_closed) << "    size: " << open_nodes.size() << '\n';
		//if (current->depth >= 81) continue;
		//cout << current->depth << '|' << i << ": ";
		if (is_solved(current))
		{
			cout << "SOLVED!\n";
			cout << current->tiles << '\n';
			break;
		}
		Vec2 zero_pos = current->tiles.get_zero_position();

		for (Vec2 move : moveset.at(zero_pos))
		{
			if (current->prev_move == -move)
			{
				continue;
			}
			GraphNode* new_node = new GraphNode(current, move);
			auto same_node = find_if(open_nodes.begin(), open_nodes.end(), [new_node](const GraphNode* n) {
				return are_tiles_same(new_node, n); });

			if (same_node == open_nodes.end())
			{
				auto insert_position = lower_bound(
					open_nodes.begin(),
					open_nodes.end(),
					new_node,
					[new_node](auto n1, auto n2) {
						//cout << get_cost(n1) << 'c' << get_cost(n2) << '\n';
						return n1->total_cost < n2->total_cost;
					}
				);
				open_nodes.insert(insert_position, new_node);
			}
			else if (new_node->depth < (*same_node)->depth)
			{
				delete *same_node;
				open_nodes.erase(same_node);
				auto insert_position = lower_bound(
					open_nodes.begin(),
					open_nodes.end(),
					new_node,
					[new_node](auto n1, auto n2) {
						//cout << get_cost(n1) << 'c' << get_cost(n2) << '\n';
						return n1->total_cost < n2->total_cost;
					}
				);
				open_nodes.insert(insert_position, new_node);
			}
			
			//else if (same_node != open_nodes.end() && )
			//{
			//	//cout << "SAME!\n";
			//	//cout << new_node->tiles << '\n';
			//	//cout << "--------\n";
			//	//cout << (*same_node)->tiles << '\n';
			//	open_nodes.erase(same_node);
			//}
			
		}

		//std::sort(
		//	open_nodes.begin(),
		//	open_nodes.end(),
		//	[](auto n1, auto n2) {
		//		return get_cost(n1) < get_cost(n2);
		//	}
		//);
		i++;
		//cout << '\n';
	}

	cout << "OUT: " << current->depth << "\n";
	for (; current != nullptr; current = current->parent)
	{
		cout << current->tiles << '\n';
	}
	cout << "Time end: " << clock.getElapsedTime().asSeconds() << " s\n";
	cout << "max: " << max_depth << "   avg: " << (total_depth / num_closed) << "    size: " << open_nodes.size() << '\n';


	//GraphNode* nn = new GraphNode(utils::get_random_tile_order(size));
	////GraphNode* nn2 = new GraphNode(nn, Vec2::UP);
	//GraphNode* nn3 = new GraphNode(Tiles({
	//	{12, 1, 10, 2},
	//	{7, 11, 4, 14},
	//	{5, 0, 9 , 15},
	//	{8, 6, 13, 3} }));
	//cout << std::boolalpha;
	//std::cout << current->tiles;
	//cout << nn2->tiles.is_solvable();
	//cout << nn3->tiles.is_solvable();
	return 0;
	//vector<vector<int>> aa = { {1,2,3},{4,5,6},{7,8,9} };
	//int* ap = (int*)aa.data();
	//for (int i = 0; i < 9; i++)
	//{
	//	cout << "-- " << *(ap + i) << '\n';
	//}
	//return 0;

	//const int width = 3;
	//const int height = 3;
	//std::vector<int> tile_list{ 1,2,3,4,5,6,7,8,9 };
	//std::shuffle(tile_list.begin(), tile_list.end(), std::default_random_engine(std::random_device()()));


	//Moveset moveset(width, height);
	//const State* state = State::create_ordered(width, height, { 8, 6, 7, 2, 5, 4, 3, 0, 1 });
	//const State* state = State::create_ordered(width, height, utils::get_random_tile_order(width, height));
	//const State* state = State::create_solved(width, height);
	//while (!state->is_solvable())
	//{
	//	state = State::create_ordered(width, height, utils::get_random_tile_order(width, height));
	//}
	//cout << state->is_solvable() << '\n';
	//return 0;
	//const State* root = state;
	//state = state->do_move(Vec2::UP);
	//state = state->do_move(Vec2::UP);
	//state = state->do_move(Vec2::LEFT);
	//state = state->do_move(Vec2::DOWN);

		//cout << 's' << state->tiles << '\n';

	//const State* curr_state = state;
	//vector<const State*> open_states;
	//vector<const State*> closed_states;
	//vector<Vec2> open_moves;
	//vector<Vec2> start_moves = moveset(state->tiles.get_zero_position());
	//open_moves.insert(open_moves.end(), start_moves.begin(), start_moves.end());

	//vector<GraphNode*> open_nodes{{}}

	//open_states.push_back(curr_state);

	//int max_iter = 125;
	//int i = 0;

	//while (!open_states.empty() && i < max_iter)
	//{
	//	//cout << i << ' ';
	//	//cout << i << '\n';
	//	//int ss = open_states.size();
	//	curr_state = utils::pop_front(open_states);
	//	//assert(ss == open_states.size() + 1);
	//	if (curr_state->is_solved())
	//	{
	//		cout << "SOLVED\n";
	//		cout << curr_state->tiles << '\n';
	//		break;
	//	}
	//	for (Vec2 move : moveset(curr_state->tiles.get_zero_position()))
	//	{
	//		//cout << move << '\n';
	//		const State* new_state = curr_state->do_move(move);
	//		//cout << 'm' << curr_state->tiles.zero_pos << " --> " << new_state->tiles.zero_pos << '\n';
	//		bool found = false;
	//		for (const State* s : closed_states)
	//		{
	//			if (s->tiles == new_state->tiles)
	//			{
	//				if (new_state->steps < s->steps)
	//				{
	//					delete s;
	//					s = new_state;
	//				}
	//				else
	//				{
	//					found = true;
	//					break;

	//				}
	//			}
	//		}
	//		if (!found)
	//			open_states.push_back(new_state);
	//	}
	//	closed_states.push_back(curr_state);
	//	sort(open_states.begin(), open_states.end(), [](const State* s1, const State* s2) {
	//		return s1->get_total_cost() < s2->get_total_cost(); 
	//	});

	//	i++;

	//	//cout << "---\n" << curr_state->tiles << '\n';
	//}

	//for (state = curr_state; state; state = state->prev_state)
	//{
	//	cout << '-' << state->tiles << '\n';

	//}

	//vector<vector<int>> tiles = { {0, 1}, {2, 3} }
	//for (int y = 0; y < height; /*y++)
	//{
	//	for (int x = 0; x < width; x++)
	//	{
	//		cout << state->tiles(x, y) << ':' << moveset(x, y) << '\n';
	//	}
	//}*/

	return 0;

	sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::End();

		window.clear();
		window.draw(shape);
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}