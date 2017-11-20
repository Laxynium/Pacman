#include "Ghost.h"
#include <random>
#include <iostream>

void Ghost::UpdateState()
{
	if(clock()-_startTime>=_timeOfBlueState)
	{
		_isBlueState = false;
		_color = _regularColor;
		_speed = 2;
		_vecToMove = _vecToMove.Normalized()*_speed;
		return;
	}
}

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
	if(_isBlueState)
	{
		UpdateState();
	}

	 Vector2D oldPosition = _position;

	 _position += _vecToMove;

	 if (_position.X()<0)
	 {
		 //TODO remove magic number which is width of game
		 _position.SetX(896 + _position.X());
	 }
	 if (_position.X() > 896)
		 _position.SetX(_position.X() - 896);

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

	auto aferNorm = _vecToMove.Normalized();

	while (_moves[randomNumber] == _vecToMove.Normalized()*-1)
		randomNumber = generate();

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

void Ghost::OnCollsion(ICollidable& collidedObject)
{
	if(collidedObject.GetTag()==Tag::Player)
	{
		std::cout << "Ghost color(" << _color.r << " " << _color.g << " " << _color.b << ") was hit by pacman\n";
	}
	//TODO if pacman took super ball back to base
	//else do nothing or something else dont know yet
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
	_isBlueState = true;
	_startTime = clock();
	_speed = 1.5;
	_vecToMove = _vecToMove.Normalized()*_speed;
}
