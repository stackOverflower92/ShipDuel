#pragma once

#ifdef _WIN32
#include <SDL.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <vector>
#include <string>

#include <assert.h>

#include "../Audio/AudioTrack.h"
#include "../Audio/AudioChunk.h"

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    void InitTrack(std::string path, std::string name);
    void InitChunk(std::string path, std::string name);

    void PlayChunk(std::string name);
    void PlayTrack(std::string name);

    void Quit();

private:
    std::vector<AudioTrack> _tracks;
    std::vector<AudioChunk> _chunks;

    Mix_Music* _GetTrackByName(std::string name);
    Mix_Chunk* _GetChunkByName(std::string name);

    int _defaultChannel = -1;
};