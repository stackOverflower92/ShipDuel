#pragma once

#include <iostream>
#include "../GameObject/Player.h"

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	static void UpdatePlayers(std::vector<Player*> players);
	static void DrawPlayers(std::vector<Player*> players);
	static std::vector<Player*> GetPlayerOpponents(Player player, std::vector<Player*> players);
	static void SetEachPlayersOpponents(std::vector<Player*> players);
	static void DestroyPlayer(Player* p);
	static void CheckWinner(std::vector<Player>* _playersRef);

private:
	std::list<Player>* _players;
};
