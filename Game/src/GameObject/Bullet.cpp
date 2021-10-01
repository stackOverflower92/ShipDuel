#include "Bullet.h"
#include "Player.h"
#include "../GameState/MainGame.h"
#include "../Debug/Debug.h"

/*!
Default constructor
*/
Bullet::Bullet()
{
}

/*!
Constructor used to initialize member variables
@param renderer A pointer to the main SDL_Renderer
@param position A 2 dimensional vector holding the position of the Bullet
@param playerDegrees The orientation of the player in degrees
@param opponentsRefList A collection containing pointers to the opponent players of the shooter (Player) of this bullet
@param owner A pointer to the Player who shot this bullet
*/
Bullet::Bullet(SDL_Renderer* renderer, Vector2 position, double playerDegrees, 
	std::vector<Player*> opponentsRefList, Player* owner)
{
	_sprite = Sprite("../media/img/laser.png", renderer, position, 15, 70);
	_sprite.SetRotation(playerDegrees);
	_opponentsRefList = opponentsRefList;
	_owner = owner;

	static int id = 0;
	_id = id++;
}

/*!
Default destructor
*/
Bullet::~Bullet()
{
}

/*!
Updates all the logic
*/
void Bullet::Update()
{
	Move();

	_CheckScreenBounds();

	for (auto& pRef : _opponentsRefList)
	{
		CheckOpponentCollision(pRef);
	}

	for (unsigned i = 0; i < AsteroidFactory::asteroids.size(); i++)
	{
		CheckAsteroidCollision(AsteroidFactory::asteroids.at(i));
	}

}

/*!
Renders every sprite on the screen
@param renderer A pointer to the main SDL_Renderer
*/
void Bullet::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopyEx(renderer, _sprite.GetTexture(), nullptr, _sprite.GetDstRectRef(), _sprite.GetRotation(), 
		nullptr, SDL_FLIP_NONE);
}

/*!
Moves the Bullet
*/
void Bullet::Move()
{
	int addx = std::cos((_sprite.GetRotation() - 90) * (M_PI / 180)) * Bullet::SPEED;
	int addy = std::sin((_sprite.GetRotation() - 90) * (M_PI / 180)) * Bullet::SPEED;

	Vector2 addVector = Vector2(addx, addy);
	Vector2 resultVector = _sprite.GetVectorPosition();

	resultVector.Add(addVector);
	_sprite.SetVectorPosition(resultVector);
}

/*!
Checks if a collision with an opponent's ship occurs
*/
void Bullet::CheckOpponentCollision(Player* o)
{
	if (o != nullptr)
	{
		if (CollisionManager::CheckCollision(_sprite.GetDstRect(), o->GetSprite().GetDstRect()))
		{
			//TODO: Remove hard-coded value down here
			o->GetDamage(5);
			_owner->DestroyBullet(*this);
		}
	}
}

/*!
 Checks if a collision with an Asteroid occurs
*/
void Bullet::CheckAsteroidCollision(Asteroid & a)
{
	if (CollisionManager::CheckCollisionIntersect(_sprite.GetDstRectRef(), a.GetSprite().GetDstRectRef()))
	{
		//TODO: Remove hard-coded value down here
		a.GetDamage(100);
		_owner->DestroyBullet(*this);
		_owner->IncrementDestroyedAsteroids();
	}
}

/*!
Destroys this bullet
*/
void Bullet::Destroy()
{
}

/*!
Gets the id of this Bullet
@return The unique id
*/
unsigned Bullet::GetId()
{
	return _id;
}

/*!
Gets the players who shot this bullet
@return A pointer to the player who shot this bullet
*/
Player* Bullet::GetOwner()
{
	return _owner;
}

/*!
Checks if this bullet is out of the viewport
@return True if thie bullet is out of the viewport, false otherwise.
*/
bool Bullet::_IsOutOfScreen()
{
	SDL_Rect screenRect = { 0, 0, MainGame::Instance()->GetScreenWidth(), MainGame::Instance()->GetScreenHeight() };
	SDL_Rect temp;

	return (SDL_IntersectRect(&screenRect, _sprite.GetDstRectRef(), &temp) == SDL_FALSE);
}

/*!
Removes itself from the game
*/
void Bullet::_DestroySelf()
{
	_owner->DestroyBullet(*this);
}

/*!
Checks if the bullet is outside of the viewport. If it is, then it gets removed from the game.
*/
void Bullet::_CheckScreenBounds()
{
	if (_IsOutOfScreen())
	{
		Debug::Log(2, "Bullet out");
		_DestroySelf();
	}
}