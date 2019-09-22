#include "Vec2.h"

Vec2::Vec2(int x, int y) : 
	x(x),
	y(y)
{}

Vec2 Vec2::operator+(const Vec2 & rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 & Vec2::operator+=(const Vec2 & rhs)
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator-(const Vec2 & rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 & Vec2::operator-=(const Vec2 & rhs)
{
	return *this = *this - rhs;
}

bool Vec2::operator==(const Vec2 & rhs) const
{
	return x == rhs.x && y == rhs.y;
}

bool Vec2::operator!=(const Vec2 & rhs) const
{
	return x != rhs.x || y != rhs.y;
}

bool Vec2::IsZero() const
{
	return x == 0 && y == 0;
}

int Vec2::LenSqr() const
{
	return x * x + y * y;
}

Vec2 Vec2::Zero()
{
	return Vec2(0, 0);
}
