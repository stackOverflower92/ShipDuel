#pragma once
#include <list>
#include <string>
#include <fstream>
#include "../Rendering/Tile.h"

class TileMap
{
public:
	TileMap();
	TileMap(std::string file, SDL_Renderer* renderer, std::string mapName, int tileWidth, int tileHeight);
	~TileMap();

	std::list<Tile> GetCollisionTiles();
	std::list<Tile> GetTiles();
	void Draw();

private:
	std::list<Tile> _tiles;
	std::list<Tile> _collisionTiles;
	std::string _file;
	std::string _name;
	int _tileWidth;
	int _tileHeight;

	struct TileInfo
	{
		std::string path;
		bool hasCollision;
	};

	void _LoadTiles();
	TileInfo _GetTileInfo(int id);
	SDL_Renderer* _renderer;
};

