#pragma once

#include <ostream>

struct Vec2
{
	int x = 0;
	int y = 0;

	Vec2() = default;
	Vec2(int x, int y) :x(x), y(y) {}

	Vec2& operator+= (Vec2 v);

	static const Vec2 UP, DOWN, LEFT, RIGHT;
};

Vec2 operator- (Vec2 v);
Vec2 operator+ (Vec2 v1, Vec2 v2);
Vec2 operator- (Vec2 v1, Vec2 v2);

std::ostream& operator<< (std::ostream& out, Vec2 v);