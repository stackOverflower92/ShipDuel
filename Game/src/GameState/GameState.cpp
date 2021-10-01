#include "GameState.h"
#include "MainGame.h"

/*!
Default constructor
*/
GameState::GameState()
{
}

/*!
Constructor used to initialize protected variables
@param _mapPath String containing the path on the filesystem of the map file
@param mapName A string containing the name of the map
@param mapTileWidth The width of a single tile of the map
@param mapTileHeight The height of a single tile of the map
@param _renderer A pointer to the main SDL_Renderer
*/
GameState::GameState(std::string _mapPath, std::string mapName, int mapTileWidth, int mapTileHeight, SDL_Renderer* _renderer)
{
	map = TileMap(_mapPath, _renderer, mapName, mapTileWidth, mapTileHeight);
	renderer = _renderer;
	MainGame* mainGame = MainGame::Instance();
	screenWidth = mainGame->GetScreenWidth();
	screenHeight = mainGame->GetScreenHeight();
	//TODO: Delete mainGame instance
}

/*!
Default destructor
*/
GameState::~GameState()
{
}

/*!
Gets a copy of the TileMap
*/
TileMap GameState::GetTileMap()
{
	return map;
}