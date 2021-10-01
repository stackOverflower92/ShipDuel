#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <stack>

#include "../GUI/MessageBox.h"

class MessageBoxFactory
{
public:
    MessageBoxFactory();
    MessageBoxFactory(SDL_Renderer* renderer);
    ~MessageBoxFactory();

    MessageBox GetCurrent();
    void Add(MessageBox mb);
    void Add(std::string title, std::string content);
    void Draw();
    void Update();

private:
    std::stack<MessageBox> _pipeline;
    SDL_Renderer* _renderer;

    void _GetInput();
};