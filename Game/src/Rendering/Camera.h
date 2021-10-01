#pragma once

#ifdef _WIN32
#include<SDL.h>
#else
#include<SDL2/SDL.h>
#endif

#include "../Math/Vector2.h"

class Camera
{
public:
	Camera();
	Camera(SDL_Rect rect);
	~Camera();

	SDL_Rect GetRect();
	void SetRect(SDL_Rect rect);
	Vector2 GetPosition();
	int GetWidth();
	int GetHeight();

private:
	SDL_Rect _rect;
};

