#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <vector>

#include "../GameObject/Asteroid.h"
#include "../Manager/TimeManager.h"

class AsteroidFactory
{
public:
    AsteroidFactory();
    AsteroidFactory(SDL_Renderer* renderer);
    ~AsteroidFactory();

    void CreateAsteroid();
    void Update();
    void Draw();
    void DestroyAsteroid(Asteroid a);
    std::vector<Asteroid> GetAsteroids();
    std::vector<Asteroid>* GetAsteroidsRef();
    static std::vector<Asteroid> asteroids;

private:
    SDL_Renderer* _renderer;
    TimeManager _timeManager;
    int _asteroidsSpawnMargin;
    int _maxAsteroidWidth;
    int _spawnTicks;

    Vector2 _GetAsteroidSpawnPosition();
};