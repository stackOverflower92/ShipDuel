#pragma once
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include <iostream>
#include "../Manager/Utils.h"
#include "../Math/Vector2.h"

class Sprite
{
public:
	enum class HLocation
	{
		Center,
		Right,
		Left
	};

	enum class VLocation
	{
		Top,
		Middle,
		Bottom
	};

	Sprite();
	Sprite(std::string texturePath, SDL_Renderer *renderer, Vector2 position, int width, int height);
	Sprite(std::string texturePath, SDL_Renderer *renderer, Vector2 position, double rotation, int width, int height);
	~Sprite();

	SDL_Point GetPosition();
	void SetPosition(SDL_Point point);
	Vector2 GetVectorPosition();
	void SetVectorPosition(Vector2 position);
	int GetWidth();
	void SetWidth(int width);
	int GetHeight();
	void SetHeight(int height);
	SDL_Texture* GetTexture();
	SDL_Rect GetDstRect();
	SDL_Rect* GetDstRectRef();
	double GetRotation();
	void SetRotation(double rotation);

	Vector2 Bottom(Sprite::HLocation l);
	Vector2 Top(Sprite::HLocation l);
	Vector2 Left(Sprite::VLocation l);
	Vector2 Right(Sprite::VLocation l);
	Vector2 Center();

	// Operators overloading
	bool operator ==(const Sprite & rhs);
	bool operator !=(const Sprite & rhs);

private:
	SDL_Rect _rect;
	Vector2 _position;
	double _rotation;
	SDL_Texture* _texture;
};

