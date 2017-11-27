#include "Ghost.h"
#include <random>
#include <iostream>
#include "MoveToPositionBehaviour.h"
#include <memory>
#include "RandomBehaviour.h"

Ghost::Ghost(IRenderer& renderer, ICollisionManager& collisionManager) : _renderer(renderer),
_collisionManager(collisionManager)
{
	_tag = Tag::Enemy;
	_width = 32;
	_height = 32;
	_position = {};
	_velocity = Vector2D{ 1,0 }*_speed;


	auto leaveBaseBehaviour = std::make_unique<MoveToPositionBehaviour>(_collisionManager);
	leaveBaseBehaviour->SetControlledGhost(this);
	leaveBaseBehaviour->SetDestination({ 448,352 });
	leaveBaseBehaviour->ReachedToDestination += std::bind(&Ghost::LeftBaseCallback, this);
	_behaviours.emplace_back(std::move(leaveBaseBehaviour));

	auto randomBehaviour = std::make_unique<RandomBehaviour>(_collisionManager);
	randomBehaviour->SetControlledGhost(this);
	_behaviours.emplace_back(std::move(randomBehaviour));

	auto returnToBaseBehaviour = std::make_unique<MoveToPositionBehaviour>(_collisionManager);
	returnToBaseBehaviour->SetControlledGhost(this);
	returnToBaseBehaviour->SetDestination({448,384});
	returnToBaseBehaviour->ReachedToDestination += std::bind(&Ghost::ReturnedToBaseCallback, this);
	_behaviours.emplace_back(std::move(returnToBaseBehaviour));

	_currentBehaviour = _behaviours[0].get();
}
void Ghost::LeftBaseCallback()
{
	if (_currentBehaviour == _behaviours[1].get()||_currentBehaviour==_behaviours[2].get())
		return;
	std::cout << "Reached to des {448,352}\n"; 
	_currentBehaviour = this->_behaviours[1].get();
}
void Ghost::ReturnedToBaseCallback()
{
	std::cout << "Reached to des {448,416}\n";
	_position=_startPosition;
	_currentBehaviour = this->_behaviours[0].get();
	_color = _regularColor;
	_isEaten = false;
	_tag = Tag::Enemy;
}
void Ghost::Draw()
{
	_renderer.FillRect(Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),
				_width,_height,{ _color } });
}

void Ghost::Update()
{
	_currentBehaviour->Update();
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


void Ghost::SetPosition(const Vector2D& newPos)
{
	GameObject::SetPosition(newPos);
	if(!_initialized)
	{
		_startPosition = newPos;
		_initialized = true;
	}
		
}

void Ghost::SetColor(const Color& color)
{
	_color=_regularColor = color;
}

void Ghost::SetTag(Tag tag)
{
	_tag = tag;
}

int Ghost::GetSpeed()
{
	return _speed;
}

void Ghost::OnPlayerPickedUpSuperBall(ICollidable&superBall)
{
	_color = { 0,0,255,0 };
	_speed = 1;
	_velocity = _velocity.Normalized()*_speed;
}

void Ghost::OnEndDurationsOfSuperBall()
{
	_color = _regularColor;
	
	if (static_cast<int>(_position.X()) % 2 == 1)_position.SetX(_position.X() + _velocity.X());
	if (static_cast<int>(_position.Y()) % 2 == 1)_position.SetY(_position.Y() + _velocity.Y());
	_speed = 2;
	_velocity = _velocity.Normalized()*_speed;
}

void Ghost::OnBeingAte(ICollidable&ghost)
{
	if (this != &ghost)
		return;
	if (_isEaten)
		return;
	if(_currentBehaviour!=_behaviours[2].get())
		_currentBehaviour = _behaviours[2].get();
	_color = { 0,0,0 };

	if (static_cast<int>(_position.X()) % 2 == 1)_position.SetX(_position.X() + _velocity.X());
	if (static_cast<int>(_position.Y()) % 2 == 1)_position.SetY(_position.Y() + _velocity.Y());
	_speed = 2;

	_isEaten = true;
	_tag = Tag::Invulnerable;
}

void Ghost::OnHitPlayer()
{
	_position = _startPosition;

	if (_currentBehaviour != _behaviours[0].get())
		_currentBehaviour = _behaviours[0].get();
}
