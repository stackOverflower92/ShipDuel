#pragma once
#include <vector>

#ifdef _WIN32
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

#include "../Manager/TextManager.h"
#include "GameState.h"

class SelectPlayers : public GameState
{
public:
	SelectPlayers();
	SelectPlayers(SDL_Renderer* renderer);
	~SelectPlayers();

	void Init() override;
	void Draw() override;
	void Update() override;

private:
	void _GetInputText();

	SDL_Renderer* _renderer;
	TextManager _textManager;
	std::string _titleText;
	std::string _inputText;
};

