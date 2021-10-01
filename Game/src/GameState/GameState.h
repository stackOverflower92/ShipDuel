#pragma once
#include "../Rendering/TileMap.h"

class GameState
{
public:
	GameState();
	GameState(std::string _mapPath, std::string mapName, int mapTileWidth, int mapTileHeight, SDL_Renderer* _renderer);
	virtual ~GameState();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	TileMap map;
	SDL_Renderer* renderer;
	int screenWidth;
	int screenHeight;

	TileMap GetTileMap();
};

