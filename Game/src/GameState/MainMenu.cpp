#include "MainMenu.h"
#include "MainGame.h"

/*!
Default constructor
*/
MainMenu::MainMenu()
{
}

/*!
Constructor used to initialize member variables
*/
MainMenu::MainMenu(SDL_Renderer* renderer, std::string mapPath)
	:GameState(mapPath, "Main Menu", MainGame::Instance()->GetScreenWidth(), MainGame::Instance()->GetScreenHeight(), renderer)
{
	_textManager = TextManager(renderer, "../media/fonts/venus.ttf", 35);
	_titleTextManager = TextManager(renderer, "../media/fonts/pdark.ttf", 50);

	_marginTop = 400;
	_titleMarginTop = 200;
	_rectMargin = 100;
	_spacing = 80;

	_options.push_back("1 Play");
	_options.push_back("2 Credits");
	_options.push_back("3 Quit");

	_menuTitle = "Ship Duel";
}

/*!
Default destructor
*/
MainMenu::~MainMenu()
{
}

/*!
Initializes this GameState
*/
void MainMenu::Init()
{
	MainGame::Instance()->GetAudioManager().PlayTrack("MainMenu");
}

/*!
Draws every Sprite and text of this GameState
*/
void MainMenu::Draw()
{
	map.Draw();
	_DrawMenuOptions();
}

/*!
Updates all the logic of this GameState
*/
void MainMenu::Update()
{
	_GetInput();
}

/*!
Gest all the input from the keyboard
*/
void MainMenu::_GetInput()
{
	std::vector<SDL_Event>& frameEvents = MainGame::Instance()->GetFrameEvents();

	for (auto& event : frameEvents)
	{
		if (event.type == SDL_KEYUP)
		{
			int pressed = event.key.keysym.sym;

			if (pressed == SDLK_1)
			{
				MainGame::Instance()->SetGameState(Utils::Playing);
			}

			if (pressed == SDLK_2)
			{
				MainGame::Instance()->SetGameState(Utils::Credits);
			}

			if (pressed == SDLK_3)
			{
				MainGame::Instance()->SetGameState(Utils::EndGame);
			}
		}
	}
}

/*!
@deprecated
Draws a rectangle used as a background for the menu
@param x X coordinate
@param y Y coordinate
@param w Width
@param h Height
@param color Background color
*/
void MainMenu::_DrawRect(int x, int y, int w, int h, SDL_Color color)
{
	SDL_Rect r = {x, y, w, h};
	SDL_Surface* s = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

	SDL_FillRect(s, &r,
	             SDL_MapRGBA(s->format, color.r, color.g, color.b, color.a));

	SDL_RenderFillRect(renderer, &r);
}

/*!
Draws the menu options
*/
void MainMenu::_DrawMenuOptions()
{
	int sw = screenWidth;
	int sx = sw / 2;
	int sy = _marginTop;
	int c = 0;

	_titleTextManager.DrawText(_menuTitle, sx, _titleMarginTop, { 255, 255, 255, 0 }, TextManager::Center);

	for (auto& o : _options)
	{
		_textManager.DrawText(o, sx, sy + (_spacing * c),
		                      {255, 255, 255, 0}, TextManager::Center);

		c++;
	}
}
