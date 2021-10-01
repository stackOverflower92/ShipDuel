#pragma once
#include "GameState.h"

class MenuGameState : GameState
{
public:
	MenuGameState();
	~MenuGameState();

	void Init();
	void Draw();
	void Update();
};

