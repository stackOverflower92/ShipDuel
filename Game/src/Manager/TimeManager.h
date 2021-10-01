#pragma once

#if _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	void Start();
	void Stop();
	void Pause();
	void Unpause();
	int GetTicks();

	bool IsStarted();
	bool IsPaused();

private:
	int _startTicks;
	int _pausedTicks;
	bool _paused;
	bool _started;
};

