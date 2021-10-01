#include "Sprite.h"
#include "../Manager/Utils.h"

/*!
Default constructor
*/
Sprite::Sprite()
{
}

/*!
Constructor used to initialize member variables
@param texturePath The path on the filesystem where the image is located
@param renderer A pointer to the main SDL_Renderer
@param position A 2 dimensional vector containing the position of the Sprite
@param width The width of the Sprite
@param height The height of the Sprite
*/
Sprite::Sprite(std::string texturePath, SDL_Renderer* renderer, Vector2 position, int width, int height)
{
	_texture = Utils::LoadTextureFromDisk(texturePath, renderer);
	_rect = {position.GetX(), position.GetY(), width, height};
	_position = position;
	_rotation = 0.0;
}

/*!
Constructor used to initialize member variables
@param texturePath The path on the filesystem where the image is located
@param renderer A pointer to the main SDL_Renderer
@param position A 2 dimensional vector containing the position of the Sprite
@param rotation The starting rotation for the Sprite in degrees
@param width The width of the Sprite
@param height The height of the Sprite
*/
Sprite::Sprite(std::string texturePath, SDL_Renderer* renderer, Vector2 position, double rotation, int width, int height)
{
	_texture = Utils::LoadTextureFromDisk(texturePath, renderer);
	_rect = {position.GetX(), position.GetY(), width, height};
	_position = position;
	_rotation = rotation;
}

/*!
Default destructor
*/
Sprite::~Sprite()
{
	
}

/*!
@deprecated
Gets the position of the Sprite
@return A SDL_Point containing the coordinates
*/
SDL_Point Sprite::GetPosition()
{
	SDL_Point point;
	point.x = _rect.x;
	point.y = _rect.y;

	return point;
}

/*!
@deprecated
Sets the position of the Sprite
@param point A SDL_Point containing the target position
*/
void Sprite::SetPosition(SDL_Point point)
{
	_rect.x = point.x;
	_rect.y = point.y;
}

/*!
Gets the position of the Sprite using a Vector2
@return A 2 dimensional vector
*/
Vector2 Sprite::GetVectorPosition()
{
	return _position;
}

/*!
Sets the position of the Sprite using a Vector2
@param position Target position
*/
void Sprite::SetVectorPosition(Vector2 position)
{
	_position = position;
}

/*!
Gets the width of the Sprite
@return The width of the sprite
*/
int Sprite::GetWidth()
{
	return _rect.w;
}

/*!
Sets the width of the Sprite
@param width The width of the sprite
*/
void Sprite::SetWidth(int width)
{
	_rect.w = width;
}

/*!
Gets the height of the Sprite
@return the height of the Sprite
*/
int Sprite::GetHeight()
{
	return _rect.h;
}

/*!
Sets the height of the Sprite
@param The height of the Sprite
*/
void Sprite::SetHeight(int height)
{
	_rect.h = height;
}

/*!
Gets the texture
@return The texture
*/
SDL_Texture* Sprite::GetTexture()
{
	return _texture;
}

/*!
Gets the destination rectangle (on the screen)
@return The rectangle
*/
SDL_Rect Sprite::GetDstRect()
{
	_rect.x = _position.GetX();
	_rect.y = _position.GetY();
	return _rect;
}

/*!
Gets a pointer to the destination rectangle (on the screen)
@return A pointer to the recrangle
*/
SDL_Rect* Sprite::GetDstRectRef()
{
	_rect.x = _position.GetX();
	_rect.y = _position.GetY();
	return &_rect;
}

/*!
Sets the rotation of the Sprite
@param rotation Target rotation
*/
void Sprite::SetRotation(double rotation)
{
	_rotation = rotation;
}

/*!
Gets the bottom local coordinate of the Sprite
@param l Location
@return The local position
*/
Vector2 Sprite::Bottom(HLocation l)
{
	int constHeight = _rect.y + _rect.h;

	switch (l)
	{
	case Sprite::HLocation::Center:
		return Vector2(_rect.x + _rect.w * 0.5, constHeight);
		break;

	case Sprite::HLocation::Left:
		return Vector2(_rect.x, constHeight);
		break;

	case Sprite::HLocation::Right:
		return Vector2(_rect.x + _rect.w, constHeight);
		break;

	default:
		return Center();
		break;
	}
}

/*!
Gets the top local coordinate of the Sprite
@param l Location
@return The local position
*/
Vector2 Sprite::Top(HLocation l)
{
	switch (l)
	{
	case Sprite::HLocation::Center:
		return Vector2(_rect.x + _rect.w * 0.5, _rect.y);
		break;

	case Sprite::HLocation::Left:
		return Vector2(_rect.x, _rect.y);
		break;

	case Sprite::HLocation::Right:
		return Vector2(_rect.x + _rect.w, _rect.y);
		break;

	default:
		return Center();
		break;
	}
}

/*!
Gets the left coorinate of the Sprite
@param l Location
@return The local position
*/
Vector2 Sprite::Left(VLocation l)
{
	switch (l)
	{
	case Sprite::VLocation::Top:
		return Vector2(_rect.x, _rect.y);
		break;

	case Sprite::VLocation::Middle:
		return Vector2(_rect.x, _rect.y + _rect.h * 0.5);
		break;

	case Sprite::VLocation::Bottom:
		return Vector2(_rect.x, _rect.y + _rect.h);
		break;

	default:
		return Center();
		break;
	}
}

/*!
Gets the right coordinate of the Sprite
@param l Location
@return The local position
*/
Vector2 Sprite::Right(VLocation l)
{
	int constWidth = _rect.x + _rect.w;

	switch (l)
	{
	case Sprite::VLocation::Top:
		return Vector2(constWidth, _rect.y);
		break;

	case Sprite::VLocation::Middle:
		return Vector2(constWidth, _rect.y + _rect.h * 0.5);
		break;

	case Sprite::VLocation::Bottom:
		return Vector2(constWidth, _rect.y + _rect.h);
		break;

	default:
		return Center();
		break;
	}
}

/*!
Gets the center of the sprite in local coordinates
@return The local position
*/
Vector2 Sprite::Center()
{
	return Vector2(_rect.x + _rect.w * 0.5, _rect.y + _rect.h * 0.5);
}

/*!
Checks if tow sprites are equals
@param rhs Other sprite
@return True if equals, false otherwise
*/
bool Sprite::operator==(const Sprite& rhs)
{
	return
		_rect.x == rhs._rect.x &&
		_rect.y == rhs._rect.y &&
		_rect.w == rhs._rect.w &&
		_rect.h == rhs._rect.h &&
		_position == rhs._position &&
		_rotation == rhs._rotation;
}

/*!
Checks if tow sprites are different
@param rhs Other sprite
@return True if equals, false otherwise
*/
bool Sprite::operator!=(const Sprite& rhs)
{
	return !operator==(rhs);
}

/*!
Gets the current rotation of the Sprite
@return The rotation expressed in degrees
*/
double Sprite::GetRotation()
{
	return _rotation;
}
