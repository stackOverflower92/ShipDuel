#include "PlayerManager.h"
#include "../GameState/MainGame.h"

/*!
Default constructor
*/
PlayerManager::PlayerManager()
{
}

/*!
Default destructor
*/
PlayerManager::~PlayerManager()
{
}

/*!
Updates the logic for every player
@param players A vector containing the pointers to the Player instances in the game
*/
void PlayerManager::UpdatePlayers(std::vector<Player*> players)
{
	for (auto& p : players)
	{
		p->Update();
	}
}

/*!
Draws every player
@param players A vector containing the pointers to the Player instances in the game
*/
void PlayerManager::DrawPlayers(std::vector<Player*> players)
{
	for (auto& p : players)
	{
		p->Draw();
	}
}

/*!
Sets the opponents for the given Player
@param player Target Player instance
@param players List of pointers to every player
@return A vector containing the pointers to the opponents
*/
std::vector<Player*> PlayerManager::GetPlayerOpponents(Player player, std::vector<Player*> players)
{
	std::vector<Player*> result;

	for (auto& p : players)
	{
		if (p->GetName() != player.GetName())
		{
			result.push_back(p);
		}
	}

	return result;
}

/*!
Sets the opponents for every Player instance
@param players A vector containing the pointers to every Player instance in the game
*/
void PlayerManager::SetEachPlayersOpponents(std::vector<Player*> players)
{
	for (auto& p : players)
	{
		p->SetOpponentsRefList(GetPlayerOpponents(*p, players));
	}
}

/*!
Removes target Player instance from the game
@param p Target Player pointer
*/
void PlayerManager::DestroyPlayer(Player* p)
{
	std::vector<Player>* pRef = MainGame::Instance()->GetPlayersRef();

	for (auto it = pRef->begin(); it != pRef->end(); )
	{
		auto currentPlayer = (*it);

		if (currentPlayer.GetName() == p->GetName())
		{
			it = pRef->erase(it);
		}
		else
		{
			++it;
		}
	}
}

/*!
Checks which Player instance is the winner of the match
@param _playersRef A pointer to the array of Player instances in the game
*/
void PlayerManager::CheckWinner(std::vector<Player>* _playersRef)
{
	if (_playersRef->size() == 1)
	{
		MainGame::Instance()->SetWinner(&_playersRef->at(0));
		MainGame::Instance()->SetGameState(Utils::Stats);
	}
}