#pragma once
#include <iostream>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "../Math/Vector2.h"

class TextManager
{
public:
	enum TextAlign
	{
		Left,
		Right,
		Center
	};

	TextManager();
	TextManager(SDL_Renderer* renderer, std::string fontName, int fontSize);
	~TextManager();

	void DrawText(std::string text, int x, int y, SDL_Color color, TextAlign align);
	void DrawText(std::string text, Vector2 position, SDL_Color color, TextAlign align);

private:
	TTF_Font* _font;
	SDL_Renderer* _renderer;
	int _fontSize;
};
