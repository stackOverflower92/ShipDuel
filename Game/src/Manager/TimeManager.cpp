#include "TimeManager.h"

/*!
Default constructor
*/
TimeManager::TimeManager()
{
	_startTicks = 0;
	_pausedTicks = 0;
	_paused = false;
	_started = false;
}

/*!
Default destructor
*/
TimeManager::~TimeManager()
{
}

/*!
Starts the timer
*/
void TimeManager::Start()
{
	_started = true;
	_paused = false;
	_startTicks = SDL_GetTicks();
	_pausedTicks = 0;
}

/*!
Stops the timer
*/
void TimeManager::Stop()
{
	_started = false;
	_paused = false;
	_startTicks = 0;
	_pausedTicks = 0;
}

/*!
Pauses the timer
*/
void TimeManager::Pause()
{
	if (_started && !_paused)
	{
		_paused = true;
		_pausedTicks = SDL_GetTicks() - _startTicks;
		_startTicks = 0;
	}
}

/*!
Unpauses the timer
*/
void TimeManager::Unpause()
{
	if (_started && _paused)
	{
		_paused = false;
		_startTicks = SDL_GetTicks() - _pausedTicks;
		_pausedTicks = 0;
	}
}

/*!
Gets the time passed since started
@return The time passed since it started
*/
int TimeManager::GetTicks()
{
	int time = 0;

	if (_started)
	{
		if (_paused)
		{
			time = _pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - _startTicks;
		}
	}
	return time;
}

/*!
Checks wether the timer is started or not
@return True if started, false otherwise
*/
bool TimeManager::IsStarted()
{
	return _started;
}

/*!
Checks wether the time has been paused or not
@return True if paused, false otherwise
*/
bool TimeManager::IsPaused()
{
	return _paused && _started;
}

