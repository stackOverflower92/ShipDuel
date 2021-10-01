#include "SelectPlayers.h"

SelectPlayers::SelectPlayers()
{
}

SelectPlayers::SelectPlayers(SDL_Renderer* renderer)
{
	_renderer = renderer;
	_textManager = TextManager(renderer, "../media/fonts/pdark.ttf", 50);

	_titleText = "How many players? (Type to decide):";
	_inputText = " ";
}

SelectPlayers::~SelectPlayers()
{
}

void SelectPlayers::Init()
{
}

void SelectPlayers::Draw()
{
	int yMargin = 200;

	_textManager.DrawText(_titleText, Vector2(1024 / 2, yMargin),
	                      {255, 255, 255, 0}, TextManager::TextAlign::Center);

	_textManager.DrawText(_inputText, Vector2(1024 / 2, yMargin * 2),
	                      {255, 255, 255, 0}, TextManager::TextAlign::Center);
}

void SelectPlayers::Update()
{
	_GetInputText();
}

void SelectPlayers::_GetInputText()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			int sym = event.key.keysym.sym;

			// Backspace
			if (sym == SDLK_BACKSPACE && _inputText.length() > 0)
			{
				_inputText.pop_back();
			}
		}
		else if (event.type == SDL_TEXTINPUT)
		{
			_inputText += event.text.text;
			std::cout << "_inputText: " << _inputText.c_str() << std::endl;
		}
	}
}
