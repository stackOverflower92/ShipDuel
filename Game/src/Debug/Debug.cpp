#include "Debug.h"

/*!
Default constructor
*/
Debug::Debug()
{

}

/*!
Default destructor
*/
Debug::~Debug()
{

}

/*!
Prints a string to the default output stream
@param level The level of debug that must be enabled.
@param content The string to be printed
*/
void Debug::Log(unsigned int level, std::string content)
{
    if (level & _MASK)
    {
        std::cout << content << std::endl;
    }
}