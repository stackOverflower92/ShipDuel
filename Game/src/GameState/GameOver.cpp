#include "GameOver.h"
#include "MainGame.h"

/*!
Default constructor
*/
GameOver::GameOver()
{

}

/*!
Constructor used to initialize member variables and parent class (GameState) protected variables
@param _renderer A pointer to the main SDL_Renderer
@param mapPath A string containing the path on the filesystem where a map file is located
*/
GameOver::GameOver(SDL_Renderer* renderer, std::string mapPath)
    : GameState(mapPath, "Game Over", MainGame::Instance()->GetScreenWidth(), MainGame::Instance()->GetScreenHeight(), renderer)
{
    _textManager = TextManager(renderer, "../media/fonts/venus.ttf", 35);
	_titleTextManager = TextManager(renderer, "../media/fonts/pdark.ttf", 50);
    
	_marginTop = 400;
	_titleMarginTop = 200;
	_rectMargin = 100;
	_spacing = 80;

	_options.push_back("1 Try Again");
    _options.push_back("2 Main Menu");
	_options.push_back("3 Quit");
}

/*!
Default destructor
*/
GameOver::~GameOver()
{

}

/*!
Initializes this GameState
*/
void GameOver::Init()
{

}

/*!
Updates all the logic of this GameState
*/
void GameOver::Update()
{
    _GetInput();
}

/*!
Draws every Sprite and text of this GameState
*/
void GameOver::Draw()
{
    map.Draw();
	//_DrawRect(0, 0, 200, 200, {0, 0, 0, 100});
	_DrawMenuOptions();
}

/*!
Gets all the input from the keyboard
*/
void GameOver::_GetInput()
{
	std::vector<SDL_Event>& frameEvents = MainGame::Instance()->GetFrameEvents();

	for (auto& event : frameEvents)
	{
		if (event.type == SDL_KEYUP)
		{
			int pressed = event.key.keysym.sym;

			if (pressed == SDLK_1)
			{
                MainGame::Instance()->ResetGame();
				MainGame::Instance()->SetGameState(Utils::Playing);
			}

			if (pressed == SDLK_2)
			{
                MainGame::Instance()->ResetGame();
				MainGame::Instance()->SetGameState(Utils::Menu);
			}

            if (pressed == SDLK_3)
			{
				MainGame::Instance()->SetGameState(Utils::EndGame);
			}
		}
	}
}

/*!
Draws the text contained in this GameState
*/
void GameOver::_DrawMenuOptions()
{
	int sw = screenWidth;
	int sx = sw / 2;
	int sy = _marginTop;
	int c = 0;

	_titleTextManager.DrawText(MainGame::Instance()->GetWinnerSentence(), sx, _titleMarginTop, { 255, 255, 255, 0 }, TextManager::Center);

	for (auto& o : _options)
	{
		_textManager.DrawText(o, sx, sy + (_spacing * c),
		                      {255, 255, 255, 0}, TextManager::Center);

		c++;
	}
}