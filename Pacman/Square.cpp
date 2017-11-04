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
	const auto oldposition = _position;
	
	_position = std::pair<int, int>{_position.first+_vecToMove.first,_position.second+_vecToMove.second};


	//TODO add multiple tags
	if (_collisionManager.DetectCollision(*this,Tag::Blocked)|| _collisionManager.DetectCollision(*this, Tag::Picker))
		_position = oldposition;

	if (_collisionManager.DetectCollision(*this, Tag::Pickable))
		;

	_vecToMove = {};
}

Rect Square::GetAreaOfCollision()const
{
	return { _position.first+1,_position.second+1,_width-1,_height-1 };
}

void Square::OnCollsion(ICollidable& collidedObject)
{
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(100, 255);
	auto generate = bind(dist, engine);

	_color = { generate(),generate(),generate(),0 };

	std::string text = (collidedObject.GetTag() == Tag::Blocked) ? ("blocked") : ("pickabe");
	std::cout << "Square was hit by " << text << std::endl;
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

