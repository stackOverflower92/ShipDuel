#include "MainGame.h"
#include "../GUI/MessageBox.h"
#include "../Debug/Debug.h"

MainGame* MainGame::_instance = nullptr;

/*!
Constructor used to initialize member variables
*/
MainGame::MainGame()
{
	_window = nullptr;
	_renderer = nullptr;
	_surface = nullptr;
	_gameName = "Ship Duel | Progetto Programmazione 2";
	_screenWidth = 1600;
	_screenHeight = 900;
	_renderWidth = 1600;
	_renderHeight = 900;
	_quit = false;
	_gameState = Utils::Menu;
	_timeManager = TimeManager();
	_timeStep = .0;
	_winner = nullptr;
	_audioManager = AudioManager();
	_enterStateCheckFlag = true;
}

/*!
Creates a unique instance of this class or gets the existing one. This is the key of the singleton pattern.
@return The only instance allowed of this class. If it does not exists, then it creates it and the returns it.
*/
MainGame* MainGame::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new MainGame;
	}
	return _instance;
}

/*!
Default destructor
*/
MainGame::~MainGame()
{
}

/*!
Initializes this game state
@param p1Name name of player 1
@param p2Name name of player 2
@param fullScreen Decides wether the applications must be launched full screen (!= 0) or not (== 0)
*/
void MainGame::Init(std::string p1Name, std::string p2Name, int fullScreen)
{
	// Save args variables for reset
	argP1Name = p1Name;
	argP2Name = p2Name;
	argFullScreen = fullScreen;

	assert(p1Name != p2Name);

	InitSystems(fullScreen);
	InitAudio();
	InitSections();
	InitEntities(p1Name, p2Name);
}

/*!
Initializes every system and subsystem of the SDL framework.
It also applies some graphics settings
@param fullScreen Decides wether the applications must be launched full screen (!= 0) or not (== 0)
*/
void MainGame::InitSystems(int fullScreen)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	TTF_Init();

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	_window = SDL_CreateWindow(_gameName.c_str(), SDL_WINDOWPOS_CENTERED,
	                           SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN);

	_renderer = SDL_CreateRenderer(_window, -1,
	                               SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	_surface = SDL_GetWindowSurface(_window);

	SDL_RenderSetLogicalSize(_renderer, _renderWidth, _renderHeight);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	if (fullScreen)
	{
		SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);	
	}

	Debug::Log(1, "InitSystems... done!");
}

/*!
Initializes every entity of the game
@param p1Name Name of player 1
@param p2Name Name of player 2
*/
void MainGame::InitEntities(std::string p1Name, std::string p2Name)
{
	Player p1 = Player("../media/img/ship.png", p1Name, _renderer, Vector2(50, _screenHeight / 2), 90.f,
	                   {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_A, SDL_SCANCODE_F});

	Player p2 = Player("../media/img/ship.png", p2Name, _renderer, Vector2(_screenWidth - 100, _screenHeight / 2), 270.f,
	                   {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT, SDL_SCANCODE_RCTRL});

	_players.push_back(p1);
	_players.push_back(p2);

	std::vector<Player*> ref;

	for (auto& p : _players)
	{
		ref.push_back(&p);
	}

	PlayerManager::SetEachPlayersOpponents(ref);

	_mainLevel = MainLevel(_renderer, "Files/level1.tmap", "Main Level", ref);

	_mbFactory = MessageBoxFactory(_renderer);

	Debug::Log(1, "InitEntities... done!");
}

/*!
Initializes AudioManager instance
*/
void MainGame::InitAudio()
{
	// Chunks
	_audioManager.InitChunk("../media/sound/laser.ogg", "laser");
	_audioManager.InitChunk("../media/sound/click.wav", "ButtonClick");

	// Tracks
	_audioManager.InitTrack("../media/sound/goliath.mp3", "Playing");
	_audioManager.InitTrack("../media/sound/music1.ogg", "MainMenu");
	
	Debug::Log(1, "InitAudio... done!");
}

/*!
Initializes every GameState
*/
void MainGame::InitSections()
{
	_mainMenu = MainMenu(_renderer, "Files/menu.tmap");
	_credits = Credits(_renderer, "Files/credits.tmap");
	_gameOver = GameOver(_renderer, "Files/gameover.tmap");

	Debug::Log(1, "InitSections... done!");
}

/*!
Gets all the Player instances
@return A vector containing all the Player instances
*/
std::vector<Player> MainGame::GetPlayers()
{
	return _players;
}

/*!
Gets a pointer to all the Player instances
@return A pointer to the vector containing all the Player instances
*/
std::vector<Player>* MainGame::GetPlayersRef()
{
	return &_players;
}

/*!
Updates all the game logic
*/
void MainGame::Update()
{
	UpdateCurrentState();
	_UpdateTimeStep();
}

/*!
Draws every sprite on the screen
*/
void MainGame::Draw()
{
	DrawCurrentState();
}

/*!
Quits every system and subsystem and frees memory
*/
void MainGame::Quit()
{
	SDL_DestroyRenderer(_renderer);
	Debug::Log(1, "SDL_DestroyRenderer... done!");

	SDL_DestroyWindow(_window);
	Debug::Log(1, "SDL_DestroyWindow... done!");

	TTF_Quit();
	Debug::Log(1, "TTF_Quit... done!");

	_audioManager.Quit();
	Mix_CloseAudio();
	Debug::Log(1, "Mix_CloseAudio and AudioManager::Quit... done!");

	SDL_Quit();
	Debug::Log(1, "SDL_Quit... done!");
}

/*!
Updates the current GameState
*/
void MainGame::UpdateCurrentState()
{
	switch (_gameState)
	{
	case Utils::Menu:
		_mainMenu.Update();
		break;

	case Utils::Credits:
		_credits.Update();
		break;

	case Utils::Playing:
		_mainLevel.Update();
		PlayerManager::CheckWinner(&_players);
		break;

	case Utils::Stats:
		_gameOver.Update();
		break;

	case Utils::EndGame:
		_quit = true;
		break;
	}

	_mbFactory.Update();
}

/*!
Draws the current GameState
*/
void MainGame::DrawCurrentState()
{
	SDL_RenderClear(_renderer);

	switch (_gameState)
	{
	case Utils::Menu:
		_mainMenu.Draw();
		break;

	case Utils::Credits:
		_credits.Draw();
		break;

	case Utils::Playing:
		_mainLevel.Draw();
		break;

	case Utils::Stats:
		_gameOver.Draw();
		break;

	case Utils::EndGame:
		_quit = true;
		break;
	}

	_mbFactory.Draw();

	SDL_RenderPresent(_renderer);
}

/*!
Sets the current GameState
@param gameState The GameState to be set
*/
void MainGame::SetGameState(Utils::GameState gameState)
{
	_gameState = gameState;
	_enterStateCheckFlag = true;
}

/*!
@deprecated
Gets a couple of values containing the width and the height of the screen
@return A 2 dimensional vector containing the width and the height of the screen
*/
Vector2 MainGame::GetScreenResolution()
{
	return Vector2(_screenWidth, _screenHeight);
}

/*!
Gets the screen width
@return The screen width
*/
int MainGame::GetScreenWidth()
{
	return _screenWidth;
}

/*!
Gets the screen height
@return The screen height
*/
int MainGame::GetScreenHeight()
{
	return _screenHeight;
}

/*!
Gets the current GameState
@return The current GameState
*/
Utils::GameState MainGame::GetGameState()
{
	return Utils::GameState();
}

/*!
Starts the Game
@param p1Name The name of the player 1
@param p2Name The name of the player 2
@param fullScreen Decides wether or not the application must be launched if fullscreen (!= 0) or ot (== 0)
*/
void MainGame::Run(std::string p1Name, std::string p2Name, int fullScreen)
{
	Init(p1Name, p2Name, fullScreen);

	while (!_quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			GetFrameEvents().push_back(event);
		}

		EnterState();
		Update();
		Draw();

		GetFrameEvents().clear();
	}

	Quit();
}

/*!
Updates the time passed since the game has started
*/
void MainGame::_UpdateTimeStep()
{
	_timeStep = _timeManager.GetTicks() / 1000.f;
}

/*!
Gets the time since the game has started
@return The time since the game has started
*/
float MainGame::GetTimeStep()
{
	return _timeStep;
}

/*!
Shows a MessageBox in the middle of the viewport
@param title The title of the MessageBox
@param content The body of the MessageBox
*/
void MainGame::ShowMessageBox(std::string title, std::string content)
{
	_mbFactory.Add(title, content);
}

/*!
Starts the TimeManager instance to calculate the time
*/
void MainGame::StartTimer()
{
	_timeManager.Start();
}

float MainGame::GetTimerTicks()
{
	return (float)_timeManager.GetTicks() / 1000.f;
}

/*!
Resets the game
*/
void MainGame::ResetGame()
{
	_ResetEntities();
	InitEntities(argP1Name, argP2Name);
	InitSections();
}

/*!
Resets every entity
*/
void MainGame::_ResetEntities()
{
	_players.clear();
	_ResetWinner();
}

/*!
Resets the winner of the game
*/
void MainGame::_ResetWinner()
{
	_winner = nullptr;
}

/*!
Sets a player as the winner of the match
@param p The winning player
*/
void MainGame::SetWinner(Player* p)
{
	_winner = p;
}

/*!
Returns a sentence to be displayed after the match has ended
@return The sentence
*/
std::string MainGame::GetWinnerSentence()
{
	if (_winner != nullptr)
		return _winner->GetName() + " won";
	return "Both players won";
}

/*!
Gets a vector containing every SDL_Event occurred in the current frame
@return Vector containing all the SDL_Event instances
*/
std::vector<SDL_Event>& MainGame::GetFrameEvents()
{
	static std::vector<SDL_Event> frameEvents;
	return frameEvents;
}

/*!
Gets a reference to the AudioManager instance
@return The reference to the AudioManager instance
*/
AudioManager& MainGame::GetAudioManager()
{
	return _audioManager;
}

/*!
Initializes the current GameState
*/
void MainGame::EnterState()
{
	if (!_enterStateCheckFlag)
	{
		return;
	}

	switch (_gameState)
	{
		case Utils::GameState::Menu:
		_mainMenu.Init();
		break;

		case Utils::GameState::Credits:
		_credits.Init();
		break;

		case Utils::GameState::Playing:
		_mainLevel.Init();
		break;

		case Utils::GameState::Stats:
		_gameOver.Init();
		break;

		case Utils::GameState::EndGame:

		break;
	}

	_enterStateCheckFlag = false;
}