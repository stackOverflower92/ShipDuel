#pragma once
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include <vector>
#include <list>

#include "../Rendering/Sprite.h"
#include "Bullet.h"
#include "../Manager/Utils.h"
#include "../Math/Vector2.h"
#include "../Rendering/TileMap.h"
#include "../Manager/TextManager.h"
#include "Flag.h"
#include "Base.h"
#include "../Manager/TimeManager.h"

class Player
{
public:
	Player();
	Player(std::string texturePath, std::string name, SDL_Renderer* renderer,
	       Vector2 position, double rotation, Utils::Keyset keyset);
	~Player();

	Sprite GetSprite();
	std::string GetName();
	void Shoot();
	void Update();
	void DrawUi();
	void Draw();
	void DrawBullets();
	void GetScanInput();
	void UpdateBullets();
	void Move(Utils::MovementDirection direction);
	void MoveLateral(Utils::MovementDirection direction);
	void MoveVertical(Utils::MovementDirection direction);
	void RotateBody(Utils::MovementDirection direction);
	void GetDamage(const int &amt);
	double GetTargetRotation(Utils::MovementDirection direction);
	void SetOpponentsRefList(std::vector<Player*> opponentsRefList);
	std::vector<Player*> GetOpponentsRefList();
	void DestroyBullet(Bullet b);
	void CheckFlags();
	void SetFlagsRefList(std::vector<Flag>* flagsRef);
	void SetRotation(double rotation);
	void SetAsteroidsRef(std::vector<Asteroid>* asteroids);
	void IncrementDestroyedAsteroids();
	int GetDestroyedAsteroids();
	std::vector<Asteroid>* GetAsteroidsRef();

	int WIDTH = 50;
	int HEIGHT = 100;
	int SPD = 7;
	int RSPD = 10;

private:
	Sprite _sprite;
	int _hp;
	std::string _name;
	std::vector<Bullet> _bullets;
	std::vector<Flag> _flags;
	Utils::Keyset _keyset;
	std::vector<Player*> _opponentsRefList;
	std::vector<Asteroid>* _asteroidsRef;
	SDL_Renderer* _renderer;
	TileMap* _level;
	bool _canMove;
	TextManager _textManager;
	std::vector<Flag>* _flagsRef;
	Base _base;
	int _dAsteroids;
	TimeManager _timeManager;
	int _shootTicks;

	static constexpr int _COOLDOWNMS = 300;

	void _CheckHp();
};

