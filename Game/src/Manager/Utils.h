#pragma once

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <iostream>

class Utils
{
public:
	Utils();
	~Utils();

	static SDL_Texture* LoadTextureFromDisk(std::string path, SDL_Renderer* renderer);
	static int Normalize(const int value, const int start, const int end);
	static int RandomRange(int min, int max);

	struct Keyset
	{
		int keyUp;
		int keyDown;
		int keyRight;
		int keyLeft;
		int keyShoot;
	};

	enum MovementDirection
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	enum GameState
	{
		Menu,
		Credits,
		Playing,
		Stats,
		EndGame
	};

	struct ScreenResolution
	{
		int w;
		int h;
	};
};

