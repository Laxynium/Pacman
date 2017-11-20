#include "Pacman.h"
#include "Rect.h"
#include <iostream>


void Pacman::Draw()
{
	_renderer.FillRect(Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height,{ _color } });
}

void Pacman::Move(const Vector2D& vec)
{
	//Cache postion
	const Vector2D oldPos = _position;
	Vector2D svec = vec;
	svec *= 2;
	_position += svec;

	//check if with new velocity pacman won't hit wall, if not accept itdw
	if(!_collisionManager.DetectCollision(*this,Tag::Wall))
	{	
		_vecToMove = svec;// vec.Normalized() * _speed;
	}

	_position = oldPos;
}

void Pacman::Update()
{
	//Cache position
	const Vector2D oldPos = _position;


	_position += _vecToMove;

	//Check if after that move won't hit wall
	if (_collisionManager.DetectCollision(*this, Tag::Wall))
	{
		_position = oldPos;
	}

	if(_position.X()<0)
	{
		//TODO remove magic number which is width of game
		_position.SetX(896 + _position.X());
	}
	if (_position.X() > 896)
		_position.SetX(_position.X()-896);
}

Rect Pacman::GetAreaOfCollision()const
{
	return { static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height};
}

void Pacman::OnCollsion(ICollidable& collidedObject)
{
	if(collidedObject.GetTag()==Tag::Enemy)
	{	
		std::cout << "Pacman hit and enemy\n";
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

	_color = { 255,255,0,0};

	_tag = Tag::Player;
}


Pacman::~Pacman()
{
}

