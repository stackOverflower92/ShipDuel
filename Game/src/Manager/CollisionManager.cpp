#include "CollisionManager.h"

/*!
Default constructor
*/
CollisionManager::CollisionManager()
{
}

/*!
Default destructor
*/
CollisionManager::~CollisionManager()
{
}

/*!
Checks wether a collision between two rectangles occurs or not
@param a First rectangle
@param b Second rectangle
@return True if they collide, false otherwise
*/
bool CollisionManager::CheckCollision(SDL_Rect a, SDL_Rect b)
{
	// The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

/*!
Checks wether a collision between two rectangles occurs or not (using native SDL function SDL_IntersectRect)
@param a A pointer to the first rectangle
@param b A pointer to the second rectangle
@return True if they collide, false otherwise
*/
bool CollisionManager::CheckCollisionIntersect(SDL_Rect* a, SDL_Rect* b)
{
	SDL_Rect* r = new SDL_Rect;
	bool retVal = false;

	if (SDL_IntersectRect(a, b, r) == SDL_TRUE)
	{
		retVal = true;
	}

	delete r;

	return retVal;
}
