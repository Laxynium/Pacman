#include "Square.h"
#include "Rect.h"
#include <SDL.h>
#include <chrono>
#include <random>
#include <functional>
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
	const auto oldposition = _position;
	
	_position = std::pair<int, int>{_position.first+_vecToMove.first,_position.second+_vecToMove.second};

	if (_collisionManager.DetectCollision(*this))
		_position = oldposition;

	_vecToMove = {};
}

Rect Square::GetAreaOfCollision()const
{
	return { _position.first+2,_position.second+2,_width-2,_height-2 };
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

}


Square::~Square()
{
}

