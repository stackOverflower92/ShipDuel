#pragma once

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <string>

#include "../Manager/TextManager.h"
#include "../Rendering/Sprite.h"

class MessageBox
{
public:
    MessageBox();
    MessageBox(std::string title, std::string content, SDL_Renderer* renderer);
    ~MessageBox();

    void Draw();

private:
    void _DrawSquare();
    void _DrawContent();
    Vector2 _GetBoxPosition();

    SDL_Renderer* _renderer;
    std::string _title;
    std::string _content;
    TextManager _textManager;
    SDL_Rect* _rect;
    Sprite _sprite;

    int _marginTop;
    int _marginBottom;
    int _marginRight;
    int _marginLeft;
    int _sw;
    int _sh;
    int _fx;
    int _fy;

    static constexpr int _IMAGEWIDTH = 492;
    static constexpr int _IMAGEHEIGHT = 212;
};