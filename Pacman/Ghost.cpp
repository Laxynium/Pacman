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


	auto behaviour = std::make_unique<MoveToPositionBehaviour>(_collisionManager);
	behaviour->SetControlledGhost(this);
	behaviour->SetDestination({ 448,352 });
	_behaviours.emplace_back(std::move(behaviour));
	auto randomBehaviour = std::make_unique<RandomBehaviour>(_collisionManager);
	randomBehaviour->SetControlledGhost(this);
	_behaviours.emplace_back(std::move(randomBehaviour));

	_clock = clock();
	_currentBehaviour = _behaviours[0].get();
}
void Ghost::Draw()
{
	_renderer.FillRect(Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),
				_width,_height,{ _color } });
}

void Ghost::Update()
{
	/*if(!_done&&clock()-_clock>=_delay)
	{
		_currentBehaviour = _behaviours[1].get();
		_done = true;
	}*/
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
	_speed = 1.5;
	_velocity = _velocity.Normalized()*_speed;
}

void Ghost::OnEndDurationsOfSuperBall()
{
	_color = _regularColor;
	_speed = 2;
	_velocity = _velocity.Normalized()*_speed;
}

void Ghost::OnBeingAte(ICollidable&ghost)
{
	if (this != &ghost)
		return;
	_currentBehaviour = _behaviours[0].get();
	_done = false;
	_clock = clock();
}

void Ghost::OnHitPlayer()
{
	_position = _startPosition;
	_currentBehaviour = _behaviours[0].get();
	_done = false;
	_clock = clock();
}
