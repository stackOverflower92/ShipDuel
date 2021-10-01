#include "Player.h"
#include "../Debug/Debug.h"
#include "../GameState/MainGame.h"
#include "../GameState/MainLevel.h"
#include <algorithm>

/*!
Default constructor
*/
Player::Player()
{
}

/*!
Constructor used to initialize member variables
@param texturePath A string containing the path on the filesystem where the image is located
@param name A string containing the name of the Player which will be displayed during the match
@param renderer A pointer to the main SDL_Renderer
@param position A 2 dimensional vector containing the position of the Player
@param rotation The rotation of the player expressed in degrees
@param keyset The set of keys used to move the player
*/
Player::Player(std::string texturePath, std::string name, SDL_Renderer* renderer,
               Vector2 position, double rotation, Utils::Keyset keyset)
{
	_sprite = Sprite(texturePath, renderer, position, rotation, Player::WIDTH, Player::HEIGHT);
	_renderer = renderer;
	_hp = 100;
	_name = name;
	_keyset = keyset;
	_canMove = true;
	_textManager = TextManager(renderer, "../media/fonts/venus.ttf", 12);
	_base = Base(position, renderer, name);
	_dAsteroids = 0;
	_timeManager = TimeManager();
	_timeManager.Start();
	_shootTicks = 0;
}

/*!
Default destructor
*/
Player::~Player()
{
}

/*!
Gets the sprite of the Player
@return A copy of the Sprite of this Player
*/
Sprite Player::GetSprite()
{
	//TODO: This rises an exception while player is shooting and not completely on screen
	return _sprite;
}

/*!
 Gets the name of this Player
 @return A string containing the name of this Player
*/
std::string Player::GetName()
{
	return _name;
}

/*!
Creates a Bullet and shoots it
*/
void Player::Shoot()
{
	int currentTicks = _timeManager.GetTicks();

	if (currentTicks - _shootTicks > _COOLDOWNMS)
	{
		Bullet b = Bullet(_renderer, _sprite.Center(), _sprite.GetRotation(), _opponentsRefList, this);
		_bullets.push_back(b);
		_shootTicks = _timeManager.GetTicks();

		MainGame::Instance()->GetAudioManager().PlayChunk("laser");
	}
}

/*!
Updates all the logic
*/
void Player::Update()
{
	GetScanInput();
	UpdateBullets();
	_CheckHp();
}

/*!
Draws the User Interface to be displayed during the match
*/
void Player::DrawUi()
{
	_textManager.DrawText(_name + " " + std::to_string(_hp) + " HP", _sprite.Bottom(Sprite::HLocation::Center),
	                      {255, 255, 255, 0}, TextManager::Center);
}

/*!
Draws every sprite on the screen
*/
void Player::Draw()
{
	if (SDL_RenderCopyEx(_renderer, _sprite.GetTexture(), nullptr, 
		_sprite.GetDstRectRef(), _sprite.GetRotation(), nullptr, SDL_FLIP_NONE) != 0)
	{
		std::cout << "SDL_RenderCopyEx error in Player::Draw: " << SDL_GetError() << std::endl;
	}

	DrawUi();

	DrawBullets();
}

/*!
Draws every shot Bullet, if any.
*/
void Player::DrawBullets()
{
	for (unsigned i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].Draw(_renderer);
	}
}

/*!
@deprecated
Gets the rotation towards which the Player will be rotating
@param The target direction
@return The target rotation expressed in degrees
*/
double Player::GetTargetRotation(Utils::MovementDirection direction)
{
	double targetRotation;

	if (direction == Utils::UP)
	{
		targetRotation = 0.0;
	}
	if (direction == Utils::DOWN)
	{
		targetRotation = 180.0;
	}
	if (direction == Utils::RIGHT)
	{
		targetRotation = 90.0;
	}
	if (direction == Utils::LEFT)
	{
		targetRotation = 270.0;
	}

	return targetRotation;
}

/*!
Sets the list containing every opponent of this Player
@param opponentsRefList The list containing the pointers to the opponents
*/
void Player::SetOpponentsRefList(std::vector<Player*> opponentsRefList)
{
	_opponentsRefList = opponentsRefList;
}

/*!
Gets the list containing every opponent of this Player
@return The list containing the pointers to the opponents
*/
std::vector<Player*> Player::GetOpponentsRefList()
{
	return _opponentsRefList;
}

/*!
@deprecated
Rotates the Sprite of the Player towards a given direction
@param direction The direction the player will be rotated towards
*/
void Player::RotateBody(Utils::MovementDirection direction)
{
	double targetRotation = GetTargetRotation(direction);
	double currentRotation = Utils::Normalize(_sprite.GetRotation(), 0, 360);

	if (targetRotation > 0.0 && targetRotation <= 180.0)
	{
		if (_sprite.GetRotation() > targetRotation)
		{
			_sprite.SetRotation(currentRotation -= 10);
		}
		else if (_sprite.GetRotation() < targetRotation)
		{
			_sprite.SetRotation(currentRotation += 10);
		}
	}
	else
	{
		if (_sprite.GetRotation() > targetRotation)
		{
			if (_sprite.GetRotation() >= 270.0 && targetRotation == 0.0)
			{
				_sprite.SetRotation(currentRotation += 10);
			}
			else
			{
				_sprite.SetRotation(currentRotation -= 10);
			}
		}
		else if (_sprite.GetRotation() < targetRotation)
		{
			if (_sprite.GetRotation() < 90.0 && targetRotation == 270.0)
			{
				int temp = currentRotation + 360;
				currentRotation = temp;

				_sprite.SetRotation(currentRotation -= 10);
			}
			else
			{
				_sprite.SetRotation(currentRotation += 10);
			}
		}
	}
}

/*!
Does damage to this Player
@param amt The amount of damage to do
*/
void Player::GetDamage(const int &amt)
{
	_hp -= amt;
}

/*!
Moves the Player vertically
@param direction The direction the Player will move towards
*/
void Player::MoveVertical(Utils::MovementDirection direction)
{
	int tx = _sprite.GetVectorPosition().GetX();
	int ty = _sprite.GetVectorPosition().GetY();

	int sh = MainGame::Instance()->GetScreenHeight();

	if (_canMove)
	{
		if (direction == Utils::UP)
		{
			ty -= SPD;
		}

		if (direction == Utils::DOWN)
		{
			ty += SPD;
		}
	}

	_sprite.SetVectorPosition(Vector2(tx, ty));

	if (ty < 0 - _sprite.GetWidth())
	{
		_sprite.SetVectorPosition(Vector2(tx, sh));
	}

	if (ty > sh + _sprite.GetWidth())
	{
		_sprite.SetVectorPosition(Vector2(tx, 0));
	}
}

/*!
@deprecated
Moves the Player horizontally
@param direction The direction the Player will move towards
*/
void Player::MoveLateral(Utils::MovementDirection direction)
{
	int tx = _sprite.GetVectorPosition().GetX();
	int ty = _sprite.GetVectorPosition().GetY();

	int sw = MainGame::Instance()->GetScreenWidth();

	if (_canMove)
	{
		if (direction == Utils::RIGHT)
		{
			tx += SPD;
		}

		if (direction == Utils::LEFT)
		{
			tx -= SPD;
		}
	}

	_sprite.SetVectorPosition(Vector2(tx, ty));

	if (tx < 0 - _sprite.GetHeight())
	{
		_sprite.SetVectorPosition(Vector2(sw, ty));
	}

	if (tx > sw + _sprite.GetHeight())
	{
		_sprite.SetVectorPosition(Vector2(0, ty));
	}
}

/*!
@deprecated
Moves the Player horizontally and vertically
@param direction The direction the Player will move towards
*/
void Player::Move(Utils::MovementDirection direction)
{
	int tx = _sprite.GetVectorPosition().GetX();
	int ty = _sprite.GetVectorPosition().GetY();

	int sw = MainGame::Instance()->GetScreenWidth();
	int sh = MainGame::Instance()->GetScreenHeight();

	if (_canMove)
	{
		if (direction == Utils::UP)
		{
			ty -= SPD;
		}
		if (direction == Utils::DOWN)
		{
			ty += SPD;
		}
		if (direction == Utils::RIGHT)
		{
			tx += SPD;
		}
		if (direction == Utils::LEFT)
		{
			tx -= SPD;
		}
	}

	_sprite.SetVectorPosition(Vector2(tx, ty));

	RotateBody(direction);

	if (tx < 0 - _sprite.GetHeight())
	{
		_sprite.SetVectorPosition(Vector2(sw, ty));
	}
	if (tx > sw + _sprite.GetHeight())
	{
		_sprite.SetVectorPosition(Vector2(0, ty));
	}
	if (ty > sh + _sprite.GetHeight())
	{
		_sprite.SetVectorPosition(Vector2(tx, 0));
	}
	if (ty < 0 - _sprite.GetHeight())
	{
		_sprite.SetVectorPosition(Vector2(tx, sh));
	}
}

/*!
Gets keyboard input
*/
void Player::GetScanInput()
{
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);

	if (keyState[_keyset.keyUp])
	{
		MoveVertical(Utils::UP);
	}

	if (keyState[_keyset.keyDown])
	{
		MoveVertical(Utils::DOWN);
	}

	if (keyState[_keyset.keyShoot])
	{
		Shoot();
	}
}

/*!
 Updates every Bullet shot by this Player, if any
*/
void Player::UpdateBullets()
{
	for (unsigned i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].Update();
	}
}

/*!
Removes a Bullet from the game
@param b The bullet which will be removed
*/
void Player::DestroyBullet(Bullet b)
{
	for (auto it = _bullets.begin(); it != _bullets.end();)
	{
		auto cBullet = (*it);

		if (cBullet.GetId() == b.GetId())
		{
			it = _bullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Player::CheckFlags()
{
	for (unsigned i = 0; i < _flagsRef->size(); i++)
	{
		if (CollisionManager::CheckCollision(_sprite.GetDstRect(), _flagsRef->at(i).GetSprite().GetDstRect()))
		{
			std::cout << "Flag taken" << std::endl;
		}
	}
}

void Player::SetFlagsRefList(std::vector<Flag>* flagsRef)
{
	_flagsRef = flagsRef;
}

/*!
Sets the rotation of the Player
@param rotation The rotation in degrees the Player will rotate towards
*/
void Player::SetRotation(double rotation)
{
	_sprite.SetRotation(rotation);
}

/*!
Checks if the Player is alive
*/
void Player::_CheckHp()
{
	if (_hp <= 0)
	{
		MainGame::Instance()->SetWinner(_opponentsRefList.front());
		MainGame::Instance()->SetGameState(Utils::GameState::Stats);
	}
}

/*!
Sets a std::vector containing the pointers to the Asteroid instances in the game
@param asteroids The std::vector containing the pointers to the Asteroid instances in the game
*/
void Player::SetAsteroidsRef(std::vector<Asteroid>* asteroids)
{
	_asteroidsRef = asteroids;
	Debug::Log(2, "Asteroids size inside player: " + std::to_string(_asteroidsRef->size()));
}

/*!
Gets a std::vector containing the pointers to the Asteroids instances in the game
@return The std::vector containing the pointers to the asteroid instances in the game
*/
std::vector<Asteroid>* Player::GetAsteroidsRef()
{
	return _asteroidsRef;
}

/*!
Increments the amount of Asteroid instances destroyed by this Player
*/
void Player::IncrementDestroyedAsteroids()
{
	_dAsteroids++;
}

/*!
Gets the amount of Asteroid instances destroyed by this player
@return The amount of destroyed Asteroid instances
*/
int Player::GetDestroyedAsteroids()
{
	return _dAsteroids;
}