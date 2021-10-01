#pragma once

#include <string>
#include <iostream>

class Debug
{
public:
    Debug();
    ~Debug();

    static void Log(unsigned int level, std::string content);
private:
    static constexpr unsigned int _MASK = 1;
};