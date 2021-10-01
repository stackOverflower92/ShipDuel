#include "Vector2.h"

/*!
Default constructor
*/
Vector2::Vector2()
{
}

/*!
Constructor used to initialize member variables
@param x X coordinate
@param y Y coordinate
*/
Vector2::Vector2(int x, int y)
{
	_x = x;
	_y = y;
}

/*!
Constructor used to initialize member variables
@param degrees Degrees
*/
Vector2::Vector2(double degrees)
{
	_x = sin(degrees);
	_y = cos(degrees);
}

/*!
Default destructor
*/
Vector2::~Vector2()
{
}

/*!
Gets the X coordinate of the vector
@return X coordinate
*/
int Vector2::GetX()
{
	return _x;
}

/*!
Gets the Y coordinate of the vector
@return Y coordinate
*/
int Vector2::GetY()
{
	return _y;
}

/*!
Sets the X coordinate of the vector
@param x The x coordinate to set
*/
void Vector2::SetX(int x)
{
	_x = x;
}

/*!
Sets the Y coordinate of the vector
@param y The y coordinate to set
*/
void Vector2::SetY(int y)
{
	_y = y;
}

/*!
Adds this vector to the parameter
@param addTo Vector to sum with
*/
void Vector2::Add(Vector2 addTo)
{
	SetX(GetX() + addTo.GetX());
	SetY(GetY() + addTo.GetY());
}

/*!
Subtracts a vector from this vector
@param subTo Other vector
*/
void Vector2::Sub(Vector2 subTo)
{
	SetX(GetX() - subTo.GetX());
	SetY(GetY() - subTo.GetY());
}

/*!
Multiplies the vector by another vector
@param mulTo Other vector
*/
void Vector2::Mul(Vector2 mulTo)
{
	SetX(GetX() * mulTo.GetX());
	SetY(GetY() * mulTo.GetY());
}

/*!
Divides this vector by another vector
@param divTo Other vector
*/
void Vector2::Div(Vector2 divTo)
{
	SetX(GetX() / divTo.GetX());
	SetY(GetY() / divTo.GetY());
}

/*!
Multiplies this vector by a scalar
@param Scalar value
*/
void Vector2::Smul(int mulTo)
{
	SetX(GetX() * mulTo);
	SetY(GetY() * mulTo);
}

double Vector2::ToDegrees()
{
	return 0.0;
}

Vector2 Vector2::DegreesToVector(double degrees)
{
	return Vector2(0, 0);
}

/*!
Checks if this vector is the same as the given one
@param ths Other vector
*/
bool Vector2::operator==(const Vector2& rhs)
{
	return _x == rhs._x && _y == rhs._y;
}

/*!
Checks if this vector is different from the given one
@param rhs Other vector
*/
bool Vector2::operator!=(const Vector2& rhs)
{
	return !operator==(rhs);
}
