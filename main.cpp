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
using namespace std;

#include "Move.h"
#include "Tiles.h"
#include "State.h"
#include "Utils.h"

int main()
{
	for_loop_yx(3, 4)
	{
		cout << x << ',' << y << '\n';
	}
	Tiles tiles = Tiles::new_from_order({ {1, 2}, {3, 0} });
	GraphNode* rr = new GraphNode(tiles);
	GraphNode* rr2 = new GraphNode(rr, Vec2::UP);
	tiles = Tiles::new_after_move(tiles, Vec2::LEFT);
	//tiles.do_move(Vec2::UP)
	//	.do_move(Vec2::LEFT)
	//	.do_move(Vec2::DOWN);
	cout << rr->tiles << '\n';
	cout << rr2->tiles << '\n';
	cout << "zero: " << tiles.get_zero_position();
	return 0;
	//vector<vector<int>> aa = { {1,2,3},{4,5,6},{7,8,9} };
	//int* ap = (int*)aa.data();
	//for (int i = 0; i < 9; i++)
	//{
	//	cout << "-- " << *(ap + i) << '\n';
	//}
	//return 0;

	const int width = 3;
	const int height = 3;
	//std::vector<int> tile_list{ 1,2,3,4,5,6,7,8,9 };
	//std::shuffle(tile_list.begin(), tile_list.end(), std::default_random_engine(std::random_device()()));


	Moveset moveset(width, height);
	//const State* state = State::create_ordered(width, height, { 8, 6, 7, 2, 5, 4, 3, 0, 1 });
	const State* state = State::create_ordered(width, height, utils::get_random_tile_order(width, height));
	//const State* state = State::create_solved(width, height);
	while (!state->is_solvable())
	{
		state = State::create_ordered(width, height, utils::get_random_tile_order(width, height));
	}
	cout << state->is_solvable() << '\n';
	//return 0;
	const State* root = state;
	//state = state->do_move(Vec2::UP);
	//state = state->do_move(Vec2::UP);
	//state = state->do_move(Vec2::LEFT);
	//state = state->do_move(Vec2::DOWN);

		cout << 's' << state->tiles << '\n';

	const State* curr_state = state;
	vector<const State*> open_states;
	vector<const State*> closed_states;
	vector<Vec2> open_moves;
	vector<Vec2> start_moves = moveset(state->tiles.get_zero_position());
	open_moves.insert(open_moves.end(), start_moves.begin(), start_moves.end());

	open_states.push_back(curr_state);

	int max_iter = 125;
	int i = 0;

	while (!open_states.empty() && i < max_iter)
	{
		//cout << i << ' ';
		//cout << i << '\n';
		//int ss = open_states.size();
		curr_state = utils::pop_front(open_states);
		//assert(ss == open_states.size() + 1);
		if (curr_state->is_solved())
		{
			cout << "SOLVED\n";
			cout << curr_state->tiles << '\n';
			break;
		}
		for (Vec2 move : moveset(curr_state->tiles.get_zero_position()))
		{
			//cout << move << '\n';
			const State* new_state = curr_state->do_move(move);
			//cout << 'm' << curr_state->tiles.zero_pos << " --> " << new_state->tiles.zero_pos << '\n';
			bool found = false;
			for (const State* s : closed_states)
			{
				if (s->tiles == new_state->tiles)
				{
					if (new_state->steps < s->steps)
					{
						delete s;
						s = new_state;
					}
					else
					{
						found = true;
						break;

					}
				}
			}
			if (!found)
				open_states.push_back(new_state);
		}
		closed_states.push_back(curr_state);
		sort(open_states.begin(), open_states.end(), [](const State* s1, const State* s2) {
			return s1->get_total_cost() < s2->get_total_cost(); 
		});

		i++;

		//cout << "---\n" << curr_state->tiles << '\n';
	}

	for (state = curr_state; state; state = state->prev_state)
	{
		cout << '-' << state->tiles << '\n';

	}

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