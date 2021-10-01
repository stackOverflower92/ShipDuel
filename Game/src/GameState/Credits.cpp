#include "Credits.h"
#include "MainGame.h"

/*!
Default constructor
*/
Credits::Credits()
{
}

/*!
Constructor used to initialize member variables and parent class (GameState) protected variables
@param _renderer A pointer to the main SDL_Renderer
@param mapPath A string containing the path on the filesystem where a map file is located
*/
Credits::Credits(SDL_Renderer* _renderer, std::string mapPath)
	: GameState(mapPath, "Credits", MainGame::Instance()->GetScreenWidth(), MainGame::Instance()->GetScreenHeight(), _renderer)
{
	_textManager = TextManager(renderer, "../media/fonts/venus.ttf", 35);
	_titleTextManager = TextManager(renderer, "../media/fonts/pdark.ttf", 50);
	_creditsText = "Tank Duel was entirely designed and coded by Giammarco Agazzotti as a project for Programmazione 2";
	_creditsTitle = "Credits";
	_titleMarginTop = 200;
	_textMarginTop = 400;
}

/*!
Default destructor
*/
Credits::~Credits()
{
}

/*!
Initializes this GameState
*/
void Credits::Init()
{
}

/*!
Draws every Sprite and text of this GameState
*/
void Credits::Draw()
{
	map.Draw();
	_DrawCreditsText();
}

/*!
Updates all the logic of this GameState
*/
void Credits::Update()
{
	_GetInput();
}

/*!
Gets all the input from the keyboard
*/
void Credits::_GetInput()
{
	std::vector<SDL_Event>& frameEvents = MainGame::Instance()->GetFrameEvents();

	for (auto& event : frameEvents)
	{
		if (event.type == SDL_KEYUP)
		{
			int pressed = event.key.keysym.sym;

			if (pressed == SDLK_ESCAPE)
			{
				MainGame::Instance()->SetGameState(Utils::Menu);
			}
		}
	}
}

/*!
Draws the text contained in this GameState
*/
void Credits::_DrawCreditsText()
{
	_titleTextManager.DrawText(_creditsTitle, screenWidth / 2, _titleMarginTop, {255, 255, 255, 0},
							TextManager::TextAlign::Center);

	_textManager.DrawText(_creditsText, screenWidth / 2, _textMarginTop, {255, 255, 255, 0},
	                      TextManager::TextAlign::Center);
}
