#include "AudioTrack.h"

/*!
 Default constructor
*/
AudioTrack::AudioTrack()
{

}

/*!
Constructor used to initialize member variables
@param music a pointer to the SDL_Mixer music that actually holds the sound
@param name a string containing the name of the music track
*/
AudioTrack::AudioTrack(Mix_Music* music, std::string name)
{
    _music = music;
    _name = name;
}

/*!
Defaul destructor
*/
AudioTrack::~AudioTrack()
{

}

/*!
Gets the Mix_Music pointer
@return A pointer to the Mix_Music value
*/
Mix_Music* AudioTrack::GetContent()
{
    return _music;
}

/*!
Gets the name of the AudioTrack
@return A string containing the name of the AudioTrack
*/
std::string AudioTrack::GetName()
{
    return _name;
}