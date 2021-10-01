#pragma once
#include <string>
#include "../Rendering/Sprite.h"

class Tile
{
public:
	Tile();
	Tile(int x, int y, std::string imagePath,
	     bool hasCollision, SDL_Renderer* renderer, int width, int height);
	~Tile();

	void Draw();
	bool HasCollision();
	Sprite GetSprite();

private:
	Sprite _sprite;
	SDL_Renderer* _renderer;
	bool _hasCollision;
	int _width;
	int _height;
};

