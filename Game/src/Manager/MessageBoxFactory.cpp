#include "MessageBoxFactory.h"
#include "../GameState/MainGame.h"

/*!
Default constructor
*/
MessageBoxFactory::MessageBoxFactory()
{

}

/*!
Constructor used to initialize member variables
@param renderer A pointer to the main SDL_Renderer
*/
MessageBoxFactory::MessageBoxFactory(SDL_Renderer* renderer)
{
    _renderer = renderer;
}

/*!
Default destructor
*/
MessageBoxFactory::~MessageBoxFactory()
{

}

/*!
Gets the current MessageBox instance in the pool
@return The MessageBox
*/
MessageBox MessageBoxFactory::GetCurrent()
{
    return _pipeline.top();
}

/*!
Adds a MessageBox to the pool
@param mb The MessageBox to be added
*/
void MessageBoxFactory::Add(MessageBox mb)
{
    _pipeline.push(mb);
}

/*!
Adds a MessageBox to the pool
@param title The title of the MessageBox
@param content The body of the MessageBox
*/
void MessageBoxFactory::Add(std::string title, std::string content)
{
    _pipeline.push(MessageBox(title, content, _renderer));
}

/*!
Gets the input for the current message box (if shown)
*/
void MessageBoxFactory::_GetInput()
{
    std::vector<SDL_Event>& frameEvents = MainGame::Instance()->GetFrameEvents();

    for (auto& event : frameEvents)
    {
        if (event.type == SDL_KEYUP)
        {
            int key = event.key.keysym.sym;

            if (key == SDLK_RETURN)
            {
                _pipeline.pop();
            }
        }
    }
}

/*!
Draws the current MessageBox
*/
void MessageBoxFactory::Draw()
{
    if (_pipeline.size() != 0)
    {
        _pipeline.top().Draw();
    }
}

/*!
Updates the logic for the MessageBox instances
*/
void MessageBoxFactory::Update()
{
    _GetInput();
}