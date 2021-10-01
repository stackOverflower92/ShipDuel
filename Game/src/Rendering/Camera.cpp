#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(SDL_Rect rect)
{
	_rect = rect;
}

Camera::~Camera()
{
}

SDL_Rect Camera::GetRect()
{
	return _rect;
}

void Camera::SetRect(SDL_Rect rect)
{
	_rect = rect;
}

Vector2 Camera::GetPosition()
{
	return Vector2(_rect.x, _rect.y);
}

int Camera::GetWidth()
{
	return _rect.w;
}

int Camera::GetHeight()
{
	return _rect.h;
}
