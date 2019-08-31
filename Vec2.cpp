#include "Vec2.h"

const Vec2 Vec2::UP(0, -1);
const Vec2 Vec2::DOWN(0, 1);
const Vec2 Vec2::LEFT(-1, 0);
const Vec2 Vec2::RIGHT(1, 0);

Vec2 operator-(Vec2 v)
{
	return Vec2(-v.x, -v.y);
}

Vec2 operator+(Vec2 v1, Vec2 v2)
{
	return Vec2(v1.x + v2.x, v1.y + v2.y);
}

Vec2 operator-(Vec2 v1, Vec2 v2)
{
	return v1 + (-v2);
}

std::ostream& operator<<(std::ostream& out, Vec2 v)
{
	out << '(' << v.x << ',' << v.y << ')';
	return out;
}

Vec2& Vec2::operator+=(Vec2 v)
{
	x += v.x;
	y += v.y;
	return *this;
}
