#include "Utils.h"
#include "../Debug/Debug.h"

/*!
Default constructor
*/
Utils::Utils()
{
}

/*!
Default destructor
*/
Utils::~Utils()
{
}

/*!
Loads a texture from disk and turns it into a SDL_Texture
@param path A string containing the path on the filesystem
@param renderer A pointer to the main SDL_Renderer
@return A pointer to a texture
*/
SDL_Texture* Utils::LoadTextureFromDisk(std::string path, SDL_Renderer* renderer)
{
	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		Debug::Log(1, "Unable to load image " + path + ": " + std::string(IMG_GetError()));
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr)
		{
			Debug::Log(1, "Unable to create texture from surface " + path + ": " + std::string(IMG_GetError()));
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

/*!
Normalizes a value between two bounds
@param value The value to normalize
@param start The lower bound
@param end The higher bound
@return The normalized value
*/
int Utils::Normalize(const int value, const int start, const int end)
{
	const int width = end - start;
	const int offsetValue = value - start;

	return (offsetValue - ((offsetValue / width) * width)) + start;
}

/*!
Returns a random number between a min and a max
@param min The lower bound
@param max The higher bound
@return The random number extracted
*/
int Utils::RandomRange(int min, int max)
{
	return rand() % max + min;
}
