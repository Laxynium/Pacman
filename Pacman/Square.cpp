#include "Square.h"
#include "Rect.h"
#include <SDL.h>
#include <chrono>
#include <random>
#include <functional>
#include <iostream>
#include <string>


void Square::Draw()
{
	_renderer.FillRect(Rect{ _position.first,_position.second,_width,_height,{_color} });
}

void Square::Move(const std::pair<int,int>& vec)
{
	_vecToMove.first += vec.first;
	_vecToMove.second += vec.second;
}

void Square::Update()
{
	if (_vecToMove == decltype(_vecToMove){})
		return;

	//Cache position
	_oldPosistion = _position;

	_position = std::pair<int, int>{ _position.first + _vecToMove.first,_position.second + _vecToMove.second };

	//Check if after that move won't hit wall
	if (_collisionManager.DetectCollision(*this, Tag::Blocked))
		_position = _oldPosistion;
	
	_vecToMove = {};
}

Rect Square::GetAreaOfCollision()const
{
	return { _position.first+1,_position.second+1,_width-1,_height-1 };
}

void Square::OnCollsion(ICollidable& collidedObject)
{
	if(collidedObject.GetTag()==Tag::Pickable)
	{	
		//_collided=true;
		//_position=_oldPosistion;
	}
}

Tag Square::GetTag() const
{
	return _tag;
}

Square::Square(IRenderer& renderer, ICollisionManager& collisionManager)
	: _renderer(renderer),_collisionManager(collisionManager)
{
	_height = 32;
	_width = 32;
	_position = { 0,0 };

	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(100, 255);
	auto generate = bind(dist, engine);

	_color = { generate(),generate(),generate(),0};

	_tag = Tag::Picker;
}


Square::~Square()
{
}

