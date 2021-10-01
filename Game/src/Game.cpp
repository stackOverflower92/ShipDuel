#include "GameState/MainGame.h"
#include <iostream>
#include <assert.h>

/**
\mainpage Ship Duel Documentation

Welcome to the docs of Ship Duel.

Ship Duel is a 2D space shooter for 2 player which puts one against the other.

A player can win by destroying more asteroids than his opponents within the time limit (60 seconds) or by killink the other player.

Player 1 will be controlled with the following keys:

W -> Move up
S -> Move down
F -> Shoot

Player 2 will be controlled with the following keys:

ARROW UP -> Move up
ARROW DOWN -> Move down
RIGHT CTRL -> Shoot

This game has to be launched with its own launcher or using the command line
typing the command: `./TankDuel <arg1> <arg2> <arg3>`

<arg1> = The name of the first player
<arg2> = The name of the second player
<arg3> = 1 to launch fullscreen, 0 to launch windowed.

To start exploring the docs in top-down mode go to Game.cpp class

*/

int main(int argc, char* args[])
{
	assert(argc == 4);

	std::string p1NameString(args[1]);
	std::string p2NameString(args[2]);
	int fullScreen = atoi(args[3]);

	MainGame* mainGame = MainGame::Instance();
	mainGame->Run(p1NameString, p2NameString, fullScreen);

	return 0;
}