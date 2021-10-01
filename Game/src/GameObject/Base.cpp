#include "Base.h"

Base::Base()
{
}

Base::Base(Vector2 position, SDL_Renderer* renderer, std::string owner)
{
	_imagePath = "../media/img/base.png";
	_sprite = Sprite(_imagePath, renderer, position, 64, 64);
	_renderer = renderer;
	_owner = owner;
	_textManager = TextManager(renderer, "../media/fonts/atwriter.ttf", 15);
}

Base::~Base()
{
}

void Base::Init()
{
	
}

void Base::Update()
{

}

void Base::Draw()
{
	SDL_RenderCopy(_renderer, _sprite.GetTexture(), nullptr, _sprite.GetDstRectRef());
	DrawUi();
}

void Base::DrawUi()
{
	_textManager.DrawText(_owner, _sprite.Center(), { 255, 255, 255, 0 }, TextManager::TextAlign::Center);
}
