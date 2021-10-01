#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include<SDL2/SDL.h>
#endif
#include "../Rendering/Sprite.h"
#include "Flag.h"
#include <vector>
#include "../Manager/TextManager.h"

class Base
{
public:
	Base();
	Base(Vector2 position, SDL_Renderer* renderer, std::string owner);
	~Base();

	void Init();
	void Update();
	void Draw();
	void DrawUi();

private:
	SDL_Renderer* _renderer;
	Sprite _sprite;
	std::string _imagePath;
	std::string _owner;
	std::vector<Flag> _collectedFlags;
	TextManager _textManager;
};

