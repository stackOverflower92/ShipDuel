#pragma once

#ifdef _WIN32
#include <SDL_ttf.h>
#include <SDL_opengl.h>
#else
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "GameState.h"
#include "../Rendering/TileMap.h"
#include "../GameObject/Player.h"
#include "../Manager/PlayerManager.h"
#include "../Manager/AsteroidFactory.h"
#include "../Manager/TimeManager.h"

class MainLevel : public GameState
{
public:
	MainLevel();
	MainLevel(SDL_Renderer* renderer, std::string mapPath,
	          std::string mapName, std::vector<Player*> playersRef);
	~MainLevel();

	void Init() override;
	void Draw() override;
	void Update() override;

private:
	std::vector<Player*> _players;
	std::vector<Flag> _flags;
	TextManager _textManager;
	TextManager _playersTextManager;
	int _flagsCount;
	AsteroidFactory _asteroidFactory;
	TimeManager _timeManager;
	int _maxTime;

	static constexpr int _MARGIN = 30;

	void _DrawUi();
	void _CheckTime();
	Player* _GetBestPlayer();
};

