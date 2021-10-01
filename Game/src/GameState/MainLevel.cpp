#include "MainLevel.h"
#include "MainGame.h"
#include "../Debug/Debug.h"
/*!
Default constructor
*/
MainLevel::MainLevel()
{
}

/*!
Constructor used to asssign member variables
*/
MainLevel::MainLevel(SDL_Renderer* renderer, std::string mapPath, std::string mapName, std::vector<Player*> playersRef)
	: GameState(mapPath, mapName, MainGame::Instance()->GetScreenWidth(), MainGame::Instance()->GetScreenHeight(), renderer)
{
	_players = playersRef;
	_textManager = TextManager(renderer, "../media/fonts/pdark.ttf", 30);
	_playersTextManager = TextManager(renderer, "../media/fonts/venus.ttf", 18);
	_flagsCount = 0;
	_asteroidFactory = AsteroidFactory(renderer);
	_timeManager = TimeManager();
	_maxTime = 120;
}

/*!
Default destructor
*/
MainLevel::~MainLevel()
{
}

/*!
Initializes this GameState
*/
void MainLevel::Init()
{
	for (int i = 0; i < _flagsCount; i++)
	{
		int tx = Utils::RandomRange(0, screenWidth);
		int ty = Utils::RandomRange(0, screenHeight);

		_flags.push_back(Flag(Vector2(tx, ty), renderer));
	}

	for (unsigned i = 0; i < _players.size(); i++)
	{
		_players.at(i)->SetFlagsRefList(&_flags);
	}

	for (unsigned i = 0; i < _players.size(); i++)
	{
		_players.at(i)->SetAsteroidsRef(_asteroidFactory.GetAsteroidsRef());
		
		Debug::Log(2, "Asteroids size outside player: " + std::to_string(_players.at(i)->GetAsteroidsRef()->size()));
	}

	MainGame::Instance()->GetAudioManager().PlayTrack("Playing");

	_timeManager.Start();
}

/*!
Draws every Sprite and text of this GameState
*/
void MainLevel::Draw()
{
	map.Draw();
	
	for (auto& f : _flags)
	{
		f.Draw();
	}

	PlayerManager::DrawPlayers(_players);
	_asteroidFactory.Draw();
	_DrawUi();
}

/*!
Updates all the logic of this GameState
*/
void MainLevel::Update()
{
	PlayerManager::UpdatePlayers(_players);
	_asteroidFactory.Update();
	_CheckTime();
}

/*!
Draws the User Interface
*/
void MainLevel::_DrawUi()
{	
	SDL_Color _timerColor = { 255, 255, 255, 0 };

	Vector2 clockPosition = Vector2(
		MainGame::Instance()->GetScreenWidth() / 2,
		_MARGIN
	);

	Vector2 p1Position = Vector2(
		_MARGIN,
		_MARGIN			
	);

	Vector2 p2Position = Vector2(
		MainGame::Instance()->GetScreenWidth() - _MARGIN,
		_MARGIN
	);

	if ((_timeManager.GetTicks() / 1000) >= _maxTime - 10)
	{
		_timerColor = { 255, 3, 3, 0 };
	}

	_textManager.DrawText(std::to_string(_timeManager.GetTicks() / 1000),
		clockPosition, _timerColor, TextManager::Center);

	_playersTextManager.DrawText(_players.front()->GetName() + ": " + std::to_string(_players.front()->GetDestroyedAsteroids()),
		p1Position, { 255, 255, 255, 0 }, TextManager::Left);

	_playersTextManager.DrawText(_players.back()->GetName() + ": " + std::to_string(_players.back()->GetDestroyedAsteroids()),
		p2Position, { 255, 255, 255, 0 }, TextManager::Right);
}

/*!
Extracts the best player, it is used at the end of the round
@return A pointer to the extracted Player
*/
Player* MainLevel::_GetBestPlayer()
{
	int maxPoints = 0;
	int bestPlayerIndex = 0;

	for (unsigned i = 0; i < _players.size(); i++)
	{
		int currentPoints = _players[i]->GetDestroyedAsteroids();

		if (currentPoints > maxPoints)
		{
			maxPoints = currentPoints;
			bestPlayerIndex = i;
		}
		else if (currentPoints == maxPoints)
		{
			bestPlayerIndex = -1;
		}
	}

	if (bestPlayerIndex == -1)
		return nullptr;

	return _players[bestPlayerIndex];
}

/*!
Checks wether or not the time of the match is over
*/
void MainLevel::_CheckTime()
{
	if ((_timeManager.GetTicks() / 1000) >= _maxTime)
	{
		MainGame::Instance()->SetWinner(_GetBestPlayer());
		MainGame::Instance()->SetGameState(Utils::Stats);
	}
}
