#pragma once
#include <list>

#include "../Rendering/Sprite.h"
#include "../Math/Vector2.h"
#include "../Manager/CollisionManager.h"
#include "Asteroid.h"

// Header is included in Bullet.cpp file to avoid recursive inclusion
class Player;

class Bullet
{
public:
	Bullet();
	Bullet(SDL_Renderer* renderer, Vector2 position, double playerDegrees, std::vector<Player*> opponentsRefList, Player* owner);
	~Bullet();

	void Update();
	void Draw(SDL_Renderer* renderer);
	void Move();
	void CheckOpponentCollision(Player* o);
	void CheckAsteroidCollision(Asteroid & a);
	void Destroy();
	unsigned GetId();
	Player* GetOwner();

	int SPEED = 10;

private:
	Sprite _sprite;
	int _damage;
	std::vector<Player*> _opponentsRefList;
	Player* _owner;
	unsigned _id;

	bool _IsOutOfScreen();
	void _DestroySelf();
	void _CheckScreenBounds();
};

