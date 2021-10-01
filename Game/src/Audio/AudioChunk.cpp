#include "AudioChunk.h"

/*!
Default constructor
*/
AudioChunk::AudioChunk()
{

}

/*!
Constructor used to initialize member variables
@param chunk a pointer to the SDL_Mixer chunk that actually holds the sound
@param name a string containing the name of the AudioChunk
*/
AudioChunk::AudioChunk(Mix_Chunk* chunk, std::string name)
{
    _chunk = chunk;
    _name = name;
}

/*!
Default destructor
*/
AudioChunk::~AudioChunk()
{

}

/*!
Gets the Mix_Chunk pointer
@return A Pointer to the Mix_Chunk value
*/
Mix_Chunk* AudioChunk::GetContent()
{
    return _chunk;
}

/*!
Gets the name of the AudioChunk
@return A string containing the name of the AudioChunk
*/
std::string AudioChunk::GetName()
{
    return _name;
}
