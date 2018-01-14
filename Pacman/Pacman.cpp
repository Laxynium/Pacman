#include "Pacman.h"
#include "Rect.h"
#include "ITextureManager.h"
#include <iostream>
#include "GameSettings.h"

Pacman::Pacman(IRenderer& renderer, ICollisionManager& collisionManager, ITextureManager&textureManager)
	: _renderer(renderer), _collisionManager(collisionManager), _textureManager(textureManager)
{
	_height = 32;
	_width = 32;
	_position = { 0,0 };

	_color = { 255,255,0,0 };

	_tag = Tag::Player;

	_currentFrame = 1;

	_framesCount = 3;

	_columnsCount = 3;
}

void Pacman::Draw()
{
	int x = (_currentFrame%_columnsCount)*(_width);
	int y = (_currentFrame / _columnsCount) * _height;

	_renderer.CopyEx(_textureManager.FindTexture(_textureName), &Rect{ x,y,_width,_height }, &Rect{ static_cast<int>(_position.X()),
		static_cast<int>(_position.Y()),_width,_height },_angle);
	//_renderer.FillRect(Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height,{ _color } });
}

void Pacman::Move(const Vector2D& vec)
{
	//Cache postion
	const Vector2D oldPos = _position;

	Vector2D svec = vec.Normalized()*_speed;

	_position += svec;

	//check if with new velocity pacman won't hit wall, if not accept it
	if(!_collisionManager.DetectCollision(*this,Tag::Wall)&& !_collisionManager.DetectCollision(*this, Tag::WallToPlayer))
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
	if (_collisionManager.DetectCollision(*this, Tag::Wall)|| _collisionManager.DetectCollision(*this, Tag::WallToPlayer))
	{
		_position = oldPos;
		_currentFrame = 1;
		return;
		//std::cout << "I am in place\n";
	}

	//Transistion between edges of map
	if(_position.X()<0)
	{
		//TODO remove magic number which is width of game
		_position.SetX(GameSettings::GameWidth + _position.X());
	}
	if (_position.X() > GameSettings::GameWidth)
		_position.SetX(_position.X()- GameSettings::GameWidth);

	//Update angle of texture
	auto diretction = _vecToMove.ToDirection();
	if (diretction.X() > 0)_angle = 0;
	else if(diretction.X()<0) _angle = -180;
	else if (diretction.Y() < 0)_angle = -90;
	else if(diretction.Y()>0) _angle = 90;
	

	//Update current frame

	if (diretction.X() == 0 && diretction.Y() == 0)
	{
		_angle = 0;
		_currentFrame = 1;
		return;
	}
	clock_t currentTime = clock();

	if(currentTime-_animClock>=_animDelay)
	{
		++_currentFrame %= _framesCount;
		_animClock = currentTime;
	}


}

Rect Pacman::GetAreaOfCollision()const
{
	return { static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height};
}


Tag Pacman::GetTag() const
{
	return _tag;
}

void Pacman::OnBeingHit()
{
	_position = _startPosition;
	_vecToMove = {};
}



void Pacman::SetPosition(const Vector2D& newPos)
{
	GameObject::SetPosition(newPos);
	_startPosition = newPos;
}


