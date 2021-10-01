#include "TileMap.h"
#include "../Debug/Debug.h"

/*!
Default constructor
*/
TileMap::TileMap()
{
}

/*!
Constructor used to initialize member variables
@param file The path on the filesystem where the tmap file is located
@param renderer A pointer to the main SDL_Renderer
@param mapName The name of the map
@param tileWidth The width of every Tile
@param tileHeight The height of every Tile
*/
TileMap::TileMap(std::string file, SDL_Renderer* renderer, std::string mapName, int tileWidth, int tileHeight)
{
	_file = file;
	_renderer = renderer;
	_name = mapName;
	_tileWidth = tileWidth;
	_tileHeight = tileHeight;

	_LoadTiles();
}

/*!
Default destructor
*/
TileMap::~TileMap()
{

}

/*!
Gets all the tiles marked as "collisions" in this TileMap
@return A list of collision Tile instances
*/
std::list<Tile> TileMap::GetCollisionTiles()
{
	return _collisionTiles;
}

/*!
Gets all the tiles in this TileMap
@return A list with all the tiles
*/
std::list<Tile> TileMap::GetTiles()
{
	return _tiles;
}

/*!
Draws all the Tile instances of this TileMap
*/
void TileMap::Draw()
{
	for (auto& t : _tiles)
	{
		t.Draw();
	}
}

/*!
Loads the TileMap from the file
*/
void TileMap::_LoadTiles()
{
	std::string line;
	std::ifstream file(_file);

	int colCounter = 0, rowCounter = 0;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			for (auto it = line.begin(); it != line.end(); ++it)
			{
				int current = (*it) - '0';
				TileInfo tileInfo = _GetTileInfo(current);

				if (tileInfo.path == "error")
				{
					Debug::Log(1, "Error while loading TileInfo");
				}

				Tile t = Tile(colCounter * _tileWidth, rowCounter * _tileHeight,
				              tileInfo.path, tileInfo.hasCollision, _renderer, _tileWidth, _tileHeight);

				_tiles.push_front(t);

				colCounter++;
			}

			rowCounter++;
			colCounter = 0;
		}
		file.close();
	}
}

/*!
Gets the informations from the current Tile
@param id The id of the Tile
@return The tile infos
*/
TileMap::TileInfo TileMap::_GetTileInfo(int id)
{
	std::ifstream file("Files/tilepairs.txt");

	int i;
	std::string path;
	int hasCollision;

	TileInfo tileInfo;

	while (file >> i >> path >> hasCollision)
	{
		if (i == id)
		{
			tileInfo.hasCollision = (hasCollision == 1);
			tileInfo.path = "../media/img/" + path;

			return tileInfo;
		}
	}

	return {"error", false};
}
