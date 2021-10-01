#pragma once
#include <vector>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	static bool CheckCollision(SDL_Rect a, SDL_Rect b);
	static bool CheckCollisionIntersect(SDL_Rect* a, SDL_Rect* b);
};
