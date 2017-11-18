#include "Ghost.h"
#include <random>
#include <iostream>

Ghost::Ghost(IRenderer& renderer, ICollisionManager& collisionManager) : _renderer(renderer),
_collisionManager(collisionManager)
{
	_tag = Tag::Enemy;
	_width = 32;
	_height = 32;
	_position = {};
	_vecToMove = { 2,0 };
}

void Ghost::Draw()
{
	_renderer.FillRect(Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),
				_width,_height,{ _color } });
}

void Ghost::Update()
{
	 Vector2D oldPosition = _position;

	 _position += _vecToMove;

	if(!_collisionManager.DetectCollision(*this,Tag::Blocked))
	{
		return;
	}

	_position = oldPosition;

	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(1, 4);
	auto generate = bind(dist, engine);

	int randomNumber = generate();

	if (randomNumber == 1)
		_vecToMove = { 2,0 };
	else if (randomNumber == 2)
		_vecToMove = { -2,0 };
	else if (randomNumber == 3)
		_vecToMove = { 0,2 };
	else if (randomNumber == 4)
		_vecToMove = { 0,-2 };

}

Rect Ghost::GetAreaOfCollision() const
{
	//x,y,w,h,color
	return Rect{ static_cast<int>(_position.X()),
		static_cast<int>(_position.Y()),_width,_height};
}

Tag Ghost::GetTag() const
{
	return _tag;
}

void Ghost::OnCollsion(ICollidable& collidedObject)
{
	if(collidedObject.GetTag()==Tag::Picker)
	{
		std::cout << "Ghost color(" << _color.r << " " << _color.g << " " << _color.b << ") was hit by pacman\n";
	}
	//TODO if pacman took super ball back to base
	//else do nothing or something else dont know yet
}

void Ghost::SetColor(const Color& color)
{
	_color = color;
}
