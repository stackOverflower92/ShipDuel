#include "Asteroid.h"
#include "../GameState/MainGame.h"
#include "../Manager/AsteroidFactory.h"

/*!
Default constructor
*/
Asteroid::Asteroid()
{

}

/*!
Constructor used to assign member variables
@param renderer A pointer to the main SDL_Renderer
@param position A 2 dimensional vector holding the position of the asteroid
@param factory A pointer to the AsteroidFactory instance
*/
Asteroid::Asteroid(SDL_Renderer* renderer, Vector2 position, AsteroidFactory *factory)
{
    _sprite = Sprite("../media/img/asteroid.png", renderer, position, (double)Utils::RandomRange(0, 359), 
        Utils::RandomRange(16, 64), Utils::RandomRange(16, 64));
    _hp = 100;
    
    _hSpeed = Utils::RandomRange(3, 5);
    _rSpeed = (float) Utils::RandomRange(2, 5);

    static int id = 0;
    _id = id++;

    _renderer = renderer;
    _asteroidFactory = factory;
}

/*!
Default destructor
*/
Asteroid::~Asteroid()
{
    
}

/*!
Updates all the logic
*/
void Asteroid::Update()
{
    Move();
    Rotate();
    _CheckScreenBounds();
}

/*!
Renders every sprite on the screen
*/
void Asteroid::Draw()
{
    SDL_RenderCopyEx(_renderer, _sprite.GetTexture(), nullptr, _sprite.GetDstRectRef(), _sprite.GetRotation(),
        nullptr, SDL_FLIP_NONE);
}

/*!
Moves the Asteroid
*/
void Asteroid::Move()
{
    Vector2 currentPosition = _sprite.GetVectorPosition();

    _sprite.SetVectorPosition(Vector2(currentPosition.GetX(), currentPosition.GetY() + _hSpeed));
}

/*!
Rotates the Asteroid
*/
void Asteroid::Rotate()
{
    double currentRotation = _sprite.GetRotation();

    _sprite.SetRotation(currentRotation + _rSpeed);
}

/*!
Gets the unique id of this Asteroid isntance
@return The id of this instance
*/
int Asteroid::GetId()
{
    return _id;
}

/*!
Checks if the Asteroid is out of the viewport
@return returns true if it is out of the viewport, false otherwise.
*/
bool Asteroid::_IsOutOfScreen()
{
	return _sprite.GetVectorPosition().GetY() >= MainGame::Instance()->GetScreenHeight();
}

/*!
Removes itself from the game
*/
void Asteroid::_DestroySelf()
{
    _asteroidFactory->DestroyAsteroid(*this);
}

/*!
If this Asteroid is out of the viewport, then it destroys itself
*/
void Asteroid::_CheckScreenBounds()
{
	if (_IsOutOfScreen())
	{
		_DestroySelf();
	}
}

/*!
 Gets the sprite
 @return The sprite
*/
Sprite Asteroid::GetSprite()
{
    return _sprite;
}

/*!
Does damage to this Asteroid
@param damage The amount of damage to be done
*/
void Asteroid::GetDamage(const int & damage)
{
    _hp -= damage;

    if (_hp <= 0)
    {
        _DestroySelf();
    }
}