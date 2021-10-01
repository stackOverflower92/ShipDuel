#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <string>
#include <vector>

#include "GameState.h"
#include "../Manager/TextManager.h"

class GameOver : public GameState
{
public:
    GameOver();
    GameOver(SDL_Renderer* renderer, std::string mapPath);
    ~GameOver();

    void Init() override;
	void Draw() override;
	void Update() override;

private:
    TextManager _textManager;
    TextManager _titleTextManager;
    std::vector<std::string> _options;
    void _DrawMenuOptions();
    void _GetInput();

    int _marginTop;
    int _titleMarginTop;
	int _rectMargin;
	int _spacing;

	int _screenWidth;
	int _screenHeight;
};