#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <iostream>
#include <list>
#include <stack>

#include "../GameObject/Player.h"
#include "../Manager/PlayerManager.h"
#include "../Rendering/TileMap.h"
#include "../Manager/Utils.h"
#include "MainMenu.h"
#include "SelectPlayers.h"
#include "Credits.h"
#include "MainLevel.h"
#include "../Manager/TimeManager.h"
#include "../Manager/MessageBoxFactory.h"
#include "GameOver.h"
#include "../Manager/AudioManager.h"

/*
	Singleton pattern
*/

class MainGame
{
public:
	static MainGame * Instance();
	~MainGame();

	void Init(std::string p1Name, std::string p2Name, int fullScreen);
	void InitSystems(int fullScreen);
	void InitEntities(std::string p1Name, std::string p2Name);
	void InitSections();
	void InitAudio();
	bool InitOpenGL();
	void Run(std::string p1Name, std::string p2Name, int fullScreen);
	void Update();
	void Draw();
	void Quit();
	void EnterState();
	void UpdateCurrentState();
	void DrawCurrentState();
	void SetGameState(Utils::GameState gameState);
	Vector2 GetScreenResolution();
	int GetScreenWidth();
	int GetScreenHeight();
	Utils::GameState GetGameState();
	std::vector<Player> GetPlayers();
	std::vector<Player>* GetPlayersRef();
	float GetTimeStep();
	void ShowMessageBox(std::string title, std::string content);
	void StartTimer();
	float GetTimerTicks();
	void ResetGame();
	void SetWinner(Player *p);
	std::string GetWinnerSentence();
	std::vector<SDL_Event>& GetFrameEvents();
	AudioManager& GetAudioManager();

private:
	MainGame();
	static MainGame* _instance;

	std::string argP1Name;
	std::string argP2Name;
	int argFullScreen;
	bool argAudioEnabled;

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Surface* _surface;
	std::string _gameName;
	int _screenWidth;
	int _screenHeight;
	int _renderWidth;
	int _renderHeight;
	bool _quit;
	std::vector<Player> _players;
	Utils::GameState _gameState;
	float _timeStep;
	MainMenu _mainMenu;
	MainLevel _mainLevel;
	Credits _credits;
	GameOver _gameOver;
	TimeManager _timeManager;
	MessageBoxFactory _mbFactory;
	Player* _winner;
	AudioManager _audioManager;
	bool _enterStateCheckFlag;

	void _UpdateTimeStep();
	void _ResetEntities();
	void _ResetWinner();
};

