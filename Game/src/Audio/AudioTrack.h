#pragma once

#ifdef _WIN32
#include <SDL.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <string>

class AudioTrack
{
public:
    AudioTrack();
    AudioTrack(Mix_Music* music, std::string name);
    ~AudioTrack();

    Mix_Music* GetContent();
    std::string GetName();

private:
    Mix_Music* _music;
    std::string _name;

};