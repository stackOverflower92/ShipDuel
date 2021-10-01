#pragma once

#ifdef _WIN32
#include <SDL.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <string>

class AudioChunk
{
public:
    AudioChunk();
    AudioChunk(Mix_Chunk* chunk, std::string name);
    ~AudioChunk();

    Mix_Chunk* GetContent();
    std::string GetName();

private:
    Mix_Chunk* _chunk;
    std::string _name;
};