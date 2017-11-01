#include "GameObject.h"



const std::pair<int, int>& GameObject::GetPosition() const
{
	return _position;
}

void GameObject::SetPostion(const std::pair<int, int>& newPos)
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
