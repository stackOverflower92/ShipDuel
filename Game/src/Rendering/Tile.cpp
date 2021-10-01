#include "Tile.h"

/*!
Default constructor
*/
Tile::Tile()
{
}

/*!
Constructor used to initialize member variables
@param x X coordinate
@param y Y coordinate
@param imagePath path of the image on the filesystem
@param renderer A pointer to the main SDL_Renderer
@param width The width of the tile
@param height The height of the tile
*/
Tile::Tile(int x, int y, std::string imagePath, bool hasCollision, SDL_Renderer* renderer, int width, int height)
{
	_renderer = renderer;
	_hasCollision = hasCollision;
	_sprite = Sprite(imagePath, renderer, Vector2(x, y), width, height);
	_width = width;
	_height = height;
}

/*!
Default destructor
*/
Tile::~Tile()
{
}

/*!
Draw the sprite
*/
void Tile::Draw()
{
	SDL_RenderCopy(_renderer, _sprite.GetTexture(), nullptr, _sprite.GetDstRectRef());
}

/*!
Check if this Tile is a collision Tile
@return True if is a collision one, false otherwise
*/
bool Tile::HasCollision()
{
	return _hasCollision;
}

/*!
Gets the Sprite
@return The Sprite
*/
Sprite Tile::GetSprite()
{
	return _sprite;
}
