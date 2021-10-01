#pragma once
#include "../Rendering/Sprite.h"

class Flag
{
public:
	Flag();
	Flag(Vector2 position, SDL_Renderer* renderer);
	~Flag();

	void Draw();
	void Update();
	Sprite GetSprite();

private:
	std::string _imagePath;
	Sprite _sprite;
	SDL_Renderer* _renderer;
};
