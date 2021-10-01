#include "Flag.h"

Flag::Flag()
{
}

Flag::Flag(Vector2 position, SDL_Renderer* renderer)
{
	_imagePath = "../media/img/canister.png";
	_renderer = renderer;
	_sprite = Sprite(_imagePath, renderer, position, 10, 21);
}

Flag::~Flag()
{
}

void Flag::Draw()
{
	SDL_RenderCopy(_renderer, _sprite.GetTexture(), nullptr, _sprite.GetDstRectRef());
}

void Flag::Update()
{
	
}

Sprite Flag::GetSprite()
{
	return _sprite;
}
