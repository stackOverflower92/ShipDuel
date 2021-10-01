#include "AsteroidFactory.h"
#include "../GameState/MainGame.h"

std::vector<Asteroid> AsteroidFactory::asteroids;

/*!
Default constructor
*/
AsteroidFactory::AsteroidFactory()
{

}

/*!
Constructor used to initialize member variables
@param renderer A pointer to the main SDL_Renderer
*/
AsteroidFactory::AsteroidFactory(SDL_Renderer* renderer)
{
    _renderer = renderer;
    _timeManager = TimeManager();
    _asteroidsSpawnMargin = 200;
    _maxAsteroidWidth = 64;
    _spawnTicks = 0;

    _timeManager.Start();
}

/*!
Default destructor
*/
AsteroidFactory::~AsteroidFactory()
{
    _timeManager.Stop();
}

/*!
Updates all the logic
*/
void AsteroidFactory::Update()
{
    int elapsed = _timeManager.GetTicks();

    if (elapsed - _spawnTicks >= Utils::RandomRange(600, 1000))
    {
        CreateAsteroid();
        _spawnTicks = _timeManager.GetTicks();
    }

    for (auto& a : asteroids)
    {
        a.Update();
    }
}

/*!
Draws every sprite
*/
void AsteroidFactory::Draw()
{
    for (auto& a : asteroids)
    {
        a.Draw();
    }
}

/*!
Removes an asteroid from the collection
@param a The Asteroid to be removed
*/
void AsteroidFactory::DestroyAsteroid(Asteroid a)
{
    for (auto it = asteroids.begin(); it != asteroids.end(); )
    {
        auto currentAsteroid = (*it);

        if (currentAsteroid.GetId() == a.GetId())
        {
            it = asteroids.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

/*!
Gets the position of the next asteroid to be spawned
@return 2 dimensional vector containing the coordinates
*/
Vector2 AsteroidFactory::_GetAsteroidSpawnPosition()
{
    return Vector2(Utils::RandomRange(_asteroidsSpawnMargin, 
        MainGame::Instance()->GetScreenWidth() - _asteroidsSpawnMargin), -10);
}

/*!
Creates a new Asteroid and adds it to the collection
*/
void AsteroidFactory::CreateAsteroid()
{
    asteroids.push_back(Asteroid(_renderer, _GetAsteroidSpawnPosition(), this));
}

/*!
Gets the vector containing all the Asteroid instances in the game
@return the vector
*/
std::vector<Asteroid> AsteroidFactory::GetAsteroids()
{
    return asteroids;
}

/*!
Gets a pointer to the vector containing all the Asteroid instances in the game
@return A pointer to the vector
*/
std::vector<Asteroid>* AsteroidFactory::GetAsteroidsRef()
{
    return &asteroids;
}