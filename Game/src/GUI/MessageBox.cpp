#include "MessageBox.h"
#include "../GameState/MainGame.h"

/*!
Default constructor
*/
MessageBox::MessageBox()
{

}

/*!
Constructor used to initialize member variables
*/
MessageBox::MessageBox(std::string title, std::string content, SDL_Renderer* renderer)
{
    _title = title;
    _content = content;
    _renderer = renderer;
    _textManager = TextManager(renderer, "../media/fonts/pdark.ttf", 20);
    _sw = MainGame::Instance()->GetScreenWidth();
    _sh = MainGame::Instance()->GetScreenHeight();
    _fx = (_sw / 2) - (_IMAGEWIDTH / 2);
    _fy = (_sh / 2) - (_IMAGEHEIGHT / 2);
    _sprite = Sprite("../media/img/messagebox.png", renderer, _GetBoxPosition(), 0.f, _IMAGEWIDTH, _IMAGEHEIGHT);
    _rect = new SDL_Rect;
    _marginTop = 200;
    _marginBottom = _sh - 200;
    _marginLeft = 200;
    _marginRight = _sw - 200;
    _rect->x = _marginRight;
    _rect->y = _marginTop;
    _rect->w = _sw - _marginRight - _marginLeft;
    _rect->h = _sh + _marginTop + _marginBottom;
}

/*!
Default destructor
*/
MessageBox::~MessageBox()
{

}

/*!
Draw sprites and text on the screen
*/
void MessageBox::Draw()
{
    _DrawSquare();
    _DrawContent();
}

/*!
Draws the background of the MessageBox
*/
void MessageBox::_DrawSquare()
{
    SDL_RenderCopy(_renderer, _sprite.GetTexture(), nullptr, _sprite.GetDstRectRef());
}

/*!
Draws the caption and the body of the MessageBox
*/
void MessageBox::_DrawContent()
{
//    _textManager.DrawText(_title, MainGame::Instance()->GetScreenWidth() / 2, _marginTop + 20, 
//        { 255, 255, 255, 0 }, TextManager::TextAlign::Center);

    _textManager.DrawText(_content, MainGame::Instance()->GetScreenWidth() / 2, _fy + _IMAGEHEIGHT / 2 - 20,
        { 255, 255, 255, 0 }, TextManager::TextAlign::Center);
}

/*!
Gets the position of the MessageBox
@return 2 dimensional vector containing the x and the y of the MessageBox
*/
Vector2 MessageBox::_GetBoxPosition()
{
    return Vector2(_fx, _fy);
}