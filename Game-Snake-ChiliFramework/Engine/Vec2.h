#pragma once
class Vec2
{
public:
	Vec2(int x = 0, int y = 0);

	Vec2 operator+(const Vec2& rhs) const;
	Vec2& operator+=(const Vec2& rhs);
	Vec2 operator-(const Vec2& rhs) const;
	Vec2& operator-=(const Vec2& rhs);
	bool operator==(const Vec2& rhs) const;
	bool operator!=(const Vec2& rhs) const;
	bool IsZero() const;
	int LenSqr() const;
	static Vec2 Zero();

public:
	int x;
	int y;
};

