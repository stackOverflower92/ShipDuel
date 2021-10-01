#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "../Math/Vector2.h"
#include "../Rendering/Sprite.h"
#include "../Manager/Utils.h"

class AsteroidFactory;

class Asteroid
{
public:
    Asteroid();
    Asteroid(SDL_Renderer* renderer, Vector2 position, AsteroidFactory* factory);
    ~Asteroid();
    
    void Update();
    void Move();
    void Rotate();
    void Draw();
    int GetId();
    Sprite GetSprite();
    void GetDamage(const int & damage);

private:
    int _hp;
    int _id;
    int _hSpeed;
    float _rSpeed;
    Sprite _sprite;
    SDL_Renderer* _renderer;
    AsteroidFactory* _asteroidFactory;

    bool _IsOutOfScreen();
    void _DestroySelf();
    void _CheckScreenBounds();
};