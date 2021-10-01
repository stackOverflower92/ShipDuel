#include "TextManager.h"
#include "../Debug/Debug.h"

/*!
Default constructor
*/
TextManager::TextManager()
{
}

/*!
Constructor used to initializa member variables
@param renderer A pointer to the main SDL_Renderer
@param fontName The path of the font in the filesystem
@param fontSize The size of the font in pixels
*/
TextManager::TextManager(SDL_Renderer* renderer, std::string fontName, int fontSize)
{
	_renderer = renderer;
	_fontSize = fontSize;
	_font = TTF_OpenFont(fontName.c_str(), fontSize);
	if (_font == nullptr)
	{
		Debug::Log(1, "Error while loading font: " + std::string(TTF_GetError()));
	}
}

/*!
Default destructor
*/
TextManager::~TextManager()
{
}

/*!
Draws a string
@param text The string
@param x The x coordinate of the text
@param y The y coordinate of the text
@param color The color of the text
@param align The alignment of the text
*/
void TextManager::DrawText(std::string text, int x, int y, SDL_Color color,
                           TextManager::TextAlign align)
{
	if (text != "")
	{
		SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(_font, text.c_str(), color, 700);
		if (surface == nullptr)
		{
			Debug::Log(1, "Text surface error: " + std::string(TTF_GetError()));
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
		if (texture == nullptr)
		{
			Debug::Log(1, "Text texture error: " + std::string(TTF_GetError()));
		}

		int dx = 0, dy = 0;
		int dw = surface->w, dh = surface->h;

		switch (align)
		{
		case Left:
			dx = x;
			dy = y;
			break;

		case Right:
			dx = x - dw;
			dy = y;
			break;

		case Center:
			dx = x - (dw / 2);
			dy = y;
			break;
		}

		SDL_Rect rect = {dx, dy, dw, dh};
		SDL_RenderCopy(_renderer, texture, NULL, &rect);
	}
}

/*!
Draws a string
@param text The string
@param position A 2 dimensional vector containing the position of the text
@param color The color of the text
@param align The alignment of the text
*/
void TextManager::DrawText(std::string text, Vector2 position, SDL_Color color, TextAlign align)
{
	if (text != "")
	{ 
		SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(_font, text.c_str(), color, 700);
		if (surface == nullptr)
		{
			Debug::Log(1, "Text surface error: " + std::string(TTF_GetError()));
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
		if (texture == nullptr)
		{
			Debug::Log(1, "Text texture error: " + std::string(TTF_GetError()));
		}

		int dx = 0, dy = 0;
		int dw = surface->w, dh = surface->h;

		switch (align)
		{
		case Left:
			dx = position.GetX();
			dy = position.GetY();
			break;

		case Right:
			dx = position.GetX() - dw;
			dy = position.GetY();
			break;

		case Center:
			dx = position.GetX() - (dw / 2);
			dy = position.GetY();
			break;
		}

		SDL_Rect rect = {dx, dy, dw, dh};
		SDL_RenderCopy(_renderer, texture, nullptr, &rect);
	}
}
