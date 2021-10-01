#pragma once
#include <vector>

#ifdef _WIN32
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#include "../Manager/TextManager.h"
#include "GameState.h"
#include "../Rendering/TileMap.h"

class MainMenu : public GameState
{
public:
	MainMenu();
	MainMenu(SDL_Renderer* renderer, std::string mapPath);
	~MainMenu();

	void Init() override;
	void Draw() override;
	void Update() override;

private:
	std::vector<std::string> _options;
	TextManager _textManager;
	TextManager _titleTextManager;

	std::string _menuTitle;

	void _DrawRect(int x, int y, int w, int h, SDL_Color color);
	void _DrawMenuOptions();
	void _GetInput();

	int _marginTop;
	int _titleMarginTop;
	int _rectMargin;
	int _spacing;

	int _screenWidth;
	int _screenHeight;
};

