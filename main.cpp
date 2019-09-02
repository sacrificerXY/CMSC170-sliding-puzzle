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
#include <bitset>
#include <inttypes.h>

#include "Moveset.h"
#include "Tiles.h"
#include "GraphNode.h"
#include "Utils.h"

#include "Array16.h"
#include <map>

using namespace std;

struct lesser_tiles
{
	bool operator()(const GraphNode* n1, const GraphNode* n2) const
	{
		return n1->tiles < n2->tiles;
	}
};

struct arr
{
	uint64_t a = 1;
};

//#define PRINT_SIZE(x) cout << "size " << typeid(x).name() << " = " << sizeof(x) << '\n';
template <typename T>
void print_size()
{
	cout << "sizeof " << typeid(T).name() << " = " << sizeof(T) << '\n';
}

pair<int, bool> num_inversions(const arrays::Array16& arr, int width, int height)
{
	int inversions = 0;

	auto indexToVec2 = [width](int i) {
		return Vec2(
			i % width
			,
			int(i / width)
		);
	};
	int zero_y;

	for (int i = 0; i < width * height; i++) {
		int val1 = get(arr, i);
		if (val1 == 0)
		{
			zero_y = i / width;
			continue;
		}
		// Check if a larger number exists after the current
		// place in the array, if so increment inversions.
		for (int j = i + 1; j < width * height; j++)
		{
			int val2 = get(arr, j);
			if (val2 == 0) continue;
			if (val1 > val2)
			{
				inversions++;
			}

		}
	}
	//return inversions;
	//cout << "zero " << zero_y << '\n';
	bool width_odd = (width % 2 == 1);
	bool inversions_even = (inversions % 2 == 0);
	bool zero_on_odd_row_from_bottom = (((height - zero_y) % 2) == 1);

	//cout << "SOLVE " << to_int_string(arr);
	//cout << "  inv=" << inversions;
	//cout << "  wid=" << width;
	//cout << "  zro=" << height-zero_y;
	//cout << '\n';

	if (width_odd && inversions_even) return pair<int, bool>(inversions, true);
	if (!width_odd && !zero_on_odd_row_from_bottom && !inversions_even) return pair<int, bool>(inversions, true);
	if (!width_odd && zero_on_odd_row_from_bottom && inversions_even) return pair<int, bool>(inversions, true);
	return pair<int, bool>(inversions, false);
}

int get_manhattan(const arrays::Array16& arr, int width, int height)
{
	Vec2 size(width, height);
	int length = size.x * size.y;
	auto arr_sol = arrays::get_ordered(width * height);
	//arr = arrays::get_ordered(width*height);
	map<int, Vec2> pos_map;
	for (int i = 0; i < length; i++)
	{
		//cout << get(arr_sol, i) << "  " << i % size.x << ',' << i /size.y << '\n';
		pos_map[get(arr_sol, i)] = Vec2( i % size.x, i / size.x );
	}
	//for (auto i : pos_map)
	//{
	//	cout << "map " << i.first << " -> " << i.second << '\n';
	//}
	//for (int i : solution)
	//{
	//	cout << i << ' ';
	//}
	//cout << '\n';

	int dist = 0;

	for (Vec2Iterator pos(size); !pos.finished(); pos++)
	{
		Vec2 delta = pos_map[get(arr, pos.y*size.x+pos.x)] - pos;
		//cout << (pos.y * size.x + pos.x) << " - " << pos << ' ' << delta << '\n';
		dist += abs(delta.x);
		dist += abs(delta.y);
	}
	return dist;
}

//int is_solvable(const arrays::Array16& arr, int width, int height)
//{
//	int inversions = num_inversions(arr, width, height);
//	bool width_odd = (width % 2 == 1);
//	bool inversions_even = (inversions % 2 == 0);
//	bool zero_on_odd_row_from_bottom = (((height - zero_y) % 1) == 1);
//
//	if (width_odd && inversions_even) return true;
//	if (!width_odd && (zero_on_odd_row_from_bottom == inversions_even)) return true;
//	return false;
//}

//bool is_solvable(conat)

struct v2
{
	uint8_t v;
};

struct Score
{
	int depth;
	int total;
	Vec2 prev_move;
};

bool operator< (const Score& s1, const Score& s2)
{
	return s1.total < s2.total;
}

int get_zero_pos(const arrays::Array16& arr)
{
	for (int i = 0; i < 16; i++)
	{
		if (get(arr, i) == 0) return i;
	}
	return -1;
}


arrays::Array16 get_move(const arrays::Array16 arr, Vec2 move, int w)
{
	auto arr2 = arr;
	int i = get_zero_pos(arr);
	//cout << "z " << i << '\n';
	if (move.y == -1)
	{
		swap(arr2, i, i-w);
	}
	else if (move.y == 1)
	{
		swap(arr2, i, i+w);
	}
	else if (move.x == -1)
	{
		swap(arr2, i, i-1);
	}
	else if (move.x == 1)
	{
		swap(arr2, i, i+1);
	}
	return arr2;
}

void print(const arrays::Array16& arr, int w, int h)
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			cout << setw(3) << get(arr, y * w + x) << ' ';
		}
		cout << '\n';
	}
}

int main()
{

	static_assert(is_pod<arrays::Array16>::value);
	static_assert(is_standard_layout<Vec2>::value);

	print_size<arrays::Array16>();
	print_size<Vec2>();
	print_size<v2>();
	print_size<std::array<arrays::Array16, 100>>();
	print_size<std::array<Vec2, 100>>();
	print_size<std::array<v2, 100>>();





	//{
	//	auto arr = arrays::get_ordered({ 6, 1, 10, 2, 7, 11, 4, 14, 5, 0, 9, 15, 8, 12, 13, 3 });
	//	//auto arr = arrays::get_ordered(16);
	//	auto [inversions, solvable] = num_inversions(arr, 4, 4);
	//	auto dist = get_manhattan(arr, 4, 4);
	//	cout << "INVERSIONS  " << inversions << '\n';
	//	cout << "SOLVABLE  " << solvable << '\n';
	//	cout << "DIST  " << dist << '\n';
	//	cout << to_bit_string(arr) << '\n';
	//	auto aa = to_array(arr);
	//	for (int i : aa)
	//	{
	//		cout << setw(2) << i << ' ';
	//	}
	//	cout << '\n';

	//	arr = get_move(arr, Vec2::UP, 4);
	//	arr = get_move(arr, Vec2::UP, 4);
	//	arr = get_move(arr, Vec2::LEFT, 4);
	//	print(arr, 4, 4);
	//	cout << '\n';


	//}
	//return 0;

	
	//return 0;

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

	//for (int i = 1; i <= 16; i++)
	//{
	//	//cout << "OR " << i << " : " << arrays::get_ordered(i) << '\n';
	//	//continue;
	//	auto arr = arrays::get_ordered(i);
	//	//swap(arr, 0, 15);
	//	std::array<int, 16> ints = to_array(arr);
	//	//cout << to_bit_string(arr) << '\n';
	//	for (int i : ints)
	//	{
	//		cout << setw(2) << i << ' ';
	//	}
	//	cout << '\n';

	//}
	//return 0;

	//uint64_t bits = utils::adler_32(utils::get_solved_tile_order({ 2,3 }));
	//cout << bitset<64>(bits).to_string() << '\n';

	//for (int i = 0; i < 16; i++)
	//{
	//	cout << i << ": " << utils::get_int(bits, i) << '\n';
	//}

	//return 0;


	Vec2 size(4, 4);
	auto root = arrays::get_ordered(utils::get_random_tile_order(size.x * size.y));
	//GraphNode* root;
	while (!(num_inversions(root, size.x, size.y).second))
	{
		root = arrays::get_ordered(utils::get_random_tile_order(size.x*size.y));
	}
	cout << std::boolalpha << !(num_inversions(root, size.x, size.y).second) << '\n';


	Moveset moveset(size);
	cout << "ROOT " << to_int_string(root) << "\n";
	print(root, size.x, size.y);



	multimap<Score, const arrays::Array16*> scores;
	map<arrays::Array16, const Score*> tiles;

	// add root to open queues
	Score score;
	score.depth = 0;
	score.total = score.depth + get_manhattan(root, size.x, size.y) + num_inversions(root, size.x, size.y).first;

	auto r = scores.insert({ score, nullptr });
	auto t = tiles.insert(make_pair( root, nullptr ));
	r->second = &t.first->first;
	t.first->second = &r->first;

	arrays::Array16 sol;
	int max_depth = 0;

	sf::Clock clock;
	int ii = 0;
	while (!scores.empty())
	{
		assert(scores.size() == tiles.size());
		auto curr = scores.begin()->first;
		auto arr = *scores.begin()->second;
		int i = get_zero_pos(arr);
		tiles.erase(tiles.find(arr));
		scores.erase(scores.begin());
		max_depth = max(max_depth, curr.depth);
		//cout << ii << ": s=" << scores.size() << " t=" << tiles.size() << " z=" << i << '\n';
		//printf("%d: %s  d=%d s=%d\n", ii, to_int_string(arr).c_str(), max_depth, curr.total);
		if (arr == arrays::get_ordered(size.x* size.y))
		{
			cout << "SOLVED!" << '\n';
			sol = arr;
			break;
		}
		for (auto v : moveset.at({ i % size.x, i / size.x }))
		{
			if (v == -curr.prev_move) continue;
			auto new_arr = get_move(arr, v, size.x);
			Score new_score;
			new_score.depth = curr.depth + 1;
			new_score.total = new_score.depth + get_manhattan(new_arr, size.x, size.y) + num_inversions(arr, size.x, size.y).first;
			new_score.prev_move = v;
			//cout << "new d=" << new_score.depth << " t=" << new_score.total << '\n';

			// find same node
			auto same_tiles = tiles.find(new_arr);

			if (same_tiles == tiles.end())
			{
				auto r = scores.insert({ new_score, nullptr });
				auto t = tiles.insert({ new_arr, nullptr });
				r->second = &t.first->first;
				t.first->second = &r->first;
			}

			else
			{
				if (new_score.depth < curr.depth)
				{
					//cout << "DELETE " << new_score.depth << " < " << curr.depth << '\n';
					auto same_score = same_tiles->second;
					scores.erase(scores.find(*same_score));
					tiles.erase(same_tiles);
					auto r = scores.insert({ new_score, nullptr });
					auto t = tiles.insert({ new_arr, nullptr });
					r->second = &t.first->first;
					t.first->second = &r->first;
				}
				else
				{

				}
			}
			
		}
		//cout << "ASAS";
		//cout << '\n';
		ii++;
	}

	print(root, size.x, size.y);
	cout << "-------------" << '\n';
	print(sol, size.x, size.y);
	cout << "Time: " << clock.getElapsedTime().asSeconds() << " s\n";
	//cout << typeid(t).name() << '\n';
	//print(t.first->first, size.x, size.y);

	//struct std::pair<
	//	class std::_Tree_iterator<
	//		class std::_Tree_val<
	//			struct std::_Tree_simple_types<
	//				struct std::pair<
	//					struct arrays::Array16 const, 
	//					struct Score* __ptr64
	//				> 
	//			> 
	//		> 
	//	>, 
	//	bool
	//>
	//cout << t << '\n';
	//print(t->first, size.x, size.y);
	//r->second = &(*t.first);

	//multiset<GraphNode*, lesser_cost> sorted_cost;
	//set<Grap
	//auto lesser_tiles = [](auto n1, auto n2) {return n1->tiles < n2->tiles; };
	//vector<GraphNode*> open_
	//set<GraphNode*, lesser_tiles> sorted_tiles;
	//open_nodes.reserve(20000);
	//sorted_cost.insert(root);
	//sorted_tiles.insert(root);

	//GraphNode* current = nullptr;
	//int i = 0;
	//int max_iter = 100000;

	//float total_depth = 0;
	//int num_closed = 0;
	//int max_depth = 0;
	//sf::Clock clock;
	//while (!sorted_cost.empty())
	//{
	//	current = *sorted_cost.begin();

	//	//auto is = find_if(sorted_tiles.begin(), sorted_tiles.end(), [current](auto n) {return n == current; });
	//	//if (is != sorted_tiles.end()) sorted_tiles.erase(is);

	//	sorted_cost.erase(sorted_cost.begin());

	//	//total_depth += current->depth;
	//	//num_closed++;
	//	max_depth = max(max_depth, current->depth);
	//	//cout << "max: " << max_depth << "   avg: " << (total_depth / num_closed) << "    size: " << sorted_cost.size() << '\n';
	//	cout << "max: " << max_depth << "    size: " << sorted_cost.size() << '\n';
	//	//if (current->depth >= 81) continue;
	//	//cout << current->depth << '|' << i << ": ";
	//	if (is_solved(current))
	//	{
	//		cout << "SOLVED!\n";
	//		cout << current->tiles << '\n';
	//		break;
	//	}
	//	Vec2 zero_pos = current->tiles.get_zero_position();

	//	for (Vec2 move : moveset.at(zero_pos))
	//	{
	//		if (current->prev_move == -move)
	//		{
	//			continue;
	//		}
	//		GraphNode* new_node = new GraphNode(current, move);
	//		//auto same_node = sorted_tiles.find(new_node);
	//		//if (same_node != sorted_tiles.end() && new_node->depth < (*same_node)->depth)
	//		//{
	//		//	sorted_cost.erase(sorted_cost.find(*same_node));
	//		//	sorted_tiles.erase(same_node);
	//		//}

	//		//if (same_node != sorted_tiles.end() && new_node->depth < (*same_node)->depth)
	//		//{
	//		//	//delete *same_node;
	//		//	//open_nodes.erase(same_node);
	//		//	//auto insert_position = lower_bound(
	//		//	//	open_nodes.begin(),
	//		//	//	open_nodes.end(),
	//		//	//	new_node,
	//		//	//	[new_node](auto n1, auto n2) {
	//		//	//		//cout << get_cost(n1) << 'c' << get_cost(n2) << '\n';
	//		//	//		return n1->total_cost < n2->total_cost;
	//		//	//	}
	//		//	//);
	//		//	//open_nodes.insert(insert_position, new_node);
	//		//}
	//		sorted_cost.insert(new_node);
	//		sorted_tiles.insert(new_node);
	//		
	//		//else if (same_node != open_nodes.end() && )
	//		//{
	//		//	//cout << "SAME!\n";
	//		//	//cout << new_node->tiles << '\n';
	//		//	//cout << "--------\n";
	//		//	//cout << (*same_node)->tiles << '\n';
	//		//	open_nodes.erase(same_node);
	//		//}
	//		
	//	}

	//	//std::sort(
	//	//	open_nodes.begin(),
	//	//	open_nodes.end(),
	//	//	[](auto n1, auto n2) {
	//	//		return get_cost(n1) < get_cost(n2);
	//	//	}
	//	//);
	//	i++;
	//	//cout << '\n';
	//}

	//cout << "OUT: " << current->depth << "\n";
	//for (; current != nullptr; current = current->parent)
	//{
	//	cout << current->tiles << '\n';
	//}
	//cout << "Time end: " << clock.getElapsedTime().asSeconds() << " s\n";
	//cout << "max: " << max_depth << "   avg: " << (total_depth / num_closed) << "    size: " << sorted_cost.size() << '\n';


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