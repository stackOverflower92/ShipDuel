#pragma once

#ifdef _WIN32
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#include <string>
#include "GameState.h"
#include "../Manager/TextManager.h"
#include "../Rendering/TileMap.h"

class Credits: public GameState
{
public:
	Credits();
	Credits(SDL_Renderer* renderer, std::string mapPath);
	~Credits();

	void Init() override;
	void Draw() override;
	void Update() override;

private:
	void _GetInput();
	void _DrawCreditsText();

	std::string _creditsText;
	std::string _creditsTitle;
	TextManager _textManager;
	TextManager _titleTextManager;
	int _titleMarginTop;
	int _textMarginTop;
};

