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
	_vecToMove = Vector2D{ 1,0 }*_speed;
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

	 const int mazeWidth = 896;
	 if (_position.X()<0)
	 {
		 //TODO remove magic number which is width of game
		 _position.SetX(mazeWidth + _position.X());
	 }
	 if (_position.X() > mazeWidth)
		 _position.SetX(_position.X() - mazeWidth);

	if(!_collisionManager.DetectCollision(*this,Tag::Wall))
	{
		return;
	}
	
	_position = oldPosition;

	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(1, 4);
	auto generate = bind(dist, engine);


	static std::map<int, Vector2D>_moves
	{
		{1,{1,0}},
		{2,{-1,0}},
		{3,{0,1}},
		{4,{0,-1}}
	};

	int randomNumber = generate();

	/*while (_moves[randomNumber] == _vecToMove.Normalized()*-1)
		randomNumber = generate();*/

	_vecToMove = _moves[randomNumber] * _speed;

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


void Ghost::SetPostion(const Vector2D& newPos)
{
	GameObject::SetPostion(newPos);
	_startPosition = newPos;
}

void Ghost::SetColor(const Color& color)
{
	_color=_regularColor = color;
}

void Ghost::SetTag(Tag tag)
{
	_tag = tag;
}

void Ghost::OnPlayerPickedUpSuperBall(ICollidable&superBall)
{
	_color = { 0,0,255,0 };
	_speed = 1.5;
	_vecToMove = _vecToMove.Normalized()*_speed;
}

void Ghost::OnEndDurationsOfSuperBall()
{
	_color = _regularColor;
	_speed = 2;
	_vecToMove = _vecToMove.Normalized()*_speed;
}

void Ghost::OnBeingAte(ICollidable&ghost)
{
	if (this != &ghost)
		return;

	_position = _startPosition;
}

void Ghost::OnHitPlayer()
{
	_position = _startPosition;
}
