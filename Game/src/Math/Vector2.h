#pragma once
#include <cmath>

class Vector2
{
public:
	Vector2();
	Vector2(int x, int y);
	Vector2(double degrees);
	~Vector2();

	int GetX();
	int GetY();
	void SetX(int x);
	void SetY(int y);

	void Add(Vector2 addTo);
	void Sub(Vector2 subTo);
	void Mul(Vector2 mulTo);
	void Div(Vector2 divTo);
	void Smul(int mulTo);

	double ToDegrees();
	static Vector2 DegreesToVector(double degrees);

	// Operators overloading
	bool operator ==(const Vector2 & rhs);
	bool operator !=(const Vector2 & rhs);

private:
	int _x;
	int _y;
};

