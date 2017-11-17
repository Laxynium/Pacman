#include "Pacman.h"
#include "Rect.h"
#include <random>
#include <functional>


void Pacman::Draw()
{
	_renderer.FillRect(Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height,{_color} });
}

void Pacman::Move(const Vector2D& vec)
{
	//Cache postion
	const Vector2D oldPos = _position;

	_position += vec.Normalized()*_speed;

	//check if with new velocity pacman won't hit wall, if not accept itdw
	if(!_collisionManager.DetectCollision(*this,Tag::Blocked))
	{	
		_vecToMove = vec.Normalized() * _speed;
	}

	_position = oldPos;
}

void Pacman::Update()
{
	//Cache position
	const Vector2D oldPos = _position;

	_position += _vecToMove;

	//Check if after that move won't hit wall
	if (_collisionManager.DetectCollision(*this, Tag::Blocked))
	{
		_position = oldPos;
	}
}

Rect Pacman::GetAreaOfCollision()const
{
	return { static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height};
}

void Pacman::OnCollsion(ICollidable& collidedObject)
{
	if(collidedObject.GetTag()==Tag::Pickable)
	{	
	}
}

Tag Pacman::GetTag() const
{
	return _tag;
}

Pacman::Pacman(IRenderer& renderer, ICollisionManager& collisionManager)
	: _renderer(renderer),_collisionManager(collisionManager)
{
	_height = 32;
	_width = 32;
	_position = { 0,0 };

	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(100, 255);
	auto generate = bind(dist, engine);

	_color = { 255,255,0,0};

	_tag = Tag::Picker;
}


Pacman::~Pacman()
{
}

