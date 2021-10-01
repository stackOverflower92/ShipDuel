#include "AudioManager.h"
#include "../Debug/Debug.h"

/*!
Default constructor
*/
AudioManager::AudioManager()
{
}

/*!
Default destructor
*/
AudioManager::~AudioManager()
{
}

/*!
Initializes an AudioChunk
@param path The path on the filesystem where the music file is located
@param name A name for the track
*/
void AudioManager::InitChunk(std::string path, std::string name)
{
    AudioChunk c = AudioChunk(Mix_LoadWAV(path.c_str()), name);
    _chunks.push_back(c);
}

/*!
Initializes an AudioTrack
@param path The path on the filesystem where the music file is located
@param name A name for the track
*/
void AudioManager::InitTrack(std::string path, std::string name)
{
    AudioTrack t = AudioTrack(Mix_LoadMUS(path.c_str()), name);
    _tracks.push_back(t);
}

/*!
Plays an AudioChunk
@param name The name of the AudioChunk to be played
*/
void AudioManager::PlayChunk(std::string name)
{
    if (Mix_PlayChannel(_defaultChannel, _GetChunkByName(name), 0) == -1)
    {
        Debug::Log(1, "Error while playing chunk: " + std::string(Mix_GetError()));
    }
}

/*!
Plays an AudioTrack
@param name The name of the AudioTrack to be played
*/
void AudioManager::PlayTrack(std::string name)
{
    if (Mix_PlayMusic(_GetTrackByName(name), -1) == -1)
    {
        Debug::Log(1, "Error while playing track: " + std::string(Mix_GetError()));
    }
}

/*!
Gets an AudioTrack filtered by name
@param The name
@return The actual track
*/
Mix_Music* AudioManager::_GetTrackByName(std::string name)
{
    Debug::Log(2, "_tracks size: " + std::to_string(_tracks.size()));

    Mix_Music* ret = nullptr;

    for (auto it = _tracks.begin(); it != _tracks.end(); ++it)
    {
        AudioTrack current = (*it);

        if (current.GetName() == name)
        {
            ret = current.GetContent();
        }
    }

    return ret;
}

/*!
Gets an AudioChunk filtered by name
@param name The name
@return The actual chunk
*/
Mix_Chunk* AudioManager::_GetChunkByName(std::string name)
{
    Debug::Log(2, "_chunks size: " + std::to_string(_chunks.size()));

    Mix_Chunk* ret = nullptr;

    for (auto it = _chunks.begin(); it != _chunks.end(); ++it)
    {
        AudioChunk current = (*it);

        if (current.GetName() == name)
        {
            Debug::Log(2, "Sound found");
            ret = current.GetContent();
        }
    }

    return ret;
}

/*!
Frees the memory
*/
void AudioManager::Quit()
{
    for (auto it = _chunks.begin(); it != _chunks.end(); ++it)
    {
        Mix_FreeChunk((*it).GetContent());
    }

    for (auto it = _tracks.begin(); it != _tracks.end(); ++it)
    {
        Mix_FreeMusic((*it).GetContent());
    }
}