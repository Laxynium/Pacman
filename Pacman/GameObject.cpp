#include "GameObject.h"


const Vector2D& GameObject::GetPosition() const
{
	return _position;
}

void GameObject::SetPosition(const Vector2D& newPos)
{
	_position = newPos;
}

const int GameObject::GetWidth() const
{
	return _width;
}

void GameObject::SetWidth(int width)
{
	_width = width;
}

const int GameObject::GetHeight() const
{
	return _height;
}

void GameObject::SetHeight(int height)
{
	_height = height;
}

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}
