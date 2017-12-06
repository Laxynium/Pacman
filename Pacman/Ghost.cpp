#include "Ghost.h"
#include <random>
#include <iostream>
#include "MoveToPositionBehaviour.h"
#include <memory>
#include "RandomBehaviour.h"
//BIG TODO refactory all of this by introducting FMS to handle all ghost states(from normal to being eaten)
Ghost::Ghost(IRenderer& renderer, ICollisionManager& collisionManager, ITextureManager&textureManager) : _renderer(renderer),
_collisionManager(collisionManager), _textureManager(textureManager)
{
	_velocity =_direction*_speed;

	SetupBehaviours();

	SetupDefaultValues();
}

void Ghost::SetupBehaviours()
{
	auto leaveBaseBehaviour = std::make_unique<MoveToPositionBehaviour>(_collisionManager);
	leaveBaseBehaviour->SetControlledGhost(this);
	leaveBaseBehaviour->SetDestination({ 448,352 });
	leaveBaseBehaviour->ReachedToDestination += std::bind(&Ghost::OnLeaveBase, this);
	_behaviours.emplace_back(std::move(leaveBaseBehaviour));

	auto randomBehaviour = std::make_unique<RandomBehaviour>(_collisionManager);
	randomBehaviour->SetControlledGhost(this);
	_behaviours.emplace_back(std::move(randomBehaviour));

	auto returnToBaseBehaviour = std::make_unique<MoveToPositionBehaviour>(_collisionManager);
	returnToBaseBehaviour->SetControlledGhost(this);
	returnToBaseBehaviour->SetDestination({ 448,384 });
	returnToBaseBehaviour->ReachedToDestination += std::bind(&Ghost::OnReturnToBase, this);
	_behaviours.emplace_back(std::move(returnToBaseBehaviour));

	_currentBehaviour = _behaviours[0].get();
}

void Ghost::SetupDefaultValues()
{
	_position = _startPosition;

	if (_behaviours.empty())
		return;

	_currentBehaviour = _behaviours[0].get();

	_color = _regularColor;

	_currentTexture = _textureName;

	_framesOffset = 0;

	_skipframesOffset = false;

	_tag = Tag::Enemy;

	_currentState = State::Base;

	_isEaten = false;

	_isColorFlashing = false;

	_speed = 2;

	_velocity = _direction*_speed;
}

//The purpose of it is fix position after change between velocity of 1 and velocity of 2
//Ghost must has countable X and Y otherwise collisions are broken
void Ghost::IncreaseVelocity()
{
	auto normalizedVelo = _direction;

	if (static_cast<int>(_position.X()) % 2 == 1)_position.SetX(_position.X() + normalizedVelo.X());

	if (static_cast<int>(_position.Y()) % 2 == 1)_position.SetY(_position.Y() + normalizedVelo.Y());

	_speed = 2;
}




void Ghost::OnLeaveBase()
{
	if (_currentBehaviour == _behaviours[1].get()||_currentBehaviour==_behaviours[2].get())
		return;
	//Change to random behaviour
	_currentBehaviour = this->_behaviours[1].get();

	_currentState = State::Normal;
}
void Ghost::OnReturnToBase()
{
	SetupDefaultValues();
}
void Ghost::Draw()
{
	int x = ((_currentFrame+ _framesOffset)%_columnsCount)*(_width);
	int y = ((_currentFrame) / _columnsCount) * _height;

	_renderer.CopyEx(_textureManager.FindTexture(_currentTexture), &Rect{x,y,_width,_height}, &Rect{ static_cast<int>(_position.X()),
		static_cast<int>(_position.Y()),_width,_height },_angle);
		
}

void Ghost::Update()
{
	_currentBehaviour->Update();

	clock_t currentTime = clock();
	if (currentTime - _animClock >= _animDelay)
	{
		++_currentFrame %= 2;
		_animClock = currentTime;
	}

	if(!_skipframesOffset)
	{
		if (_direction.X() > 0)
			_framesOffset = 0;
		else if (_direction.X() < 0)
			_framesOffset = 2;

		else if (_direction.Y() < 0)
			_framesOffset = 4;
		else if (_direction.Y() > 0)
			_framesOffset = 6;
	}


	if(_isColorFlashing&&_currentState!=State::BackToBase)
	{
		clock_t modDiff = clock() - _colorFlashingStart;
		if (modDiff>=60)
		{
			if (_currentTexture == _eatableTextureName)
				_currentTexture = _whiteTextureName;
			else
				_currentTexture = _eatableTextureName;

			_framesOffset = 0;

			_skipframesOffset = true;

			if (_tempColor == Color{ 0,0,255,0 })
				_tempColor = { 255,255,255,0 };
			else
				_tempColor = { 0,0,255,0 };

			_color = _tempColor;

			_colorFlashingStart = clock();
		}	
		return;
	}

	

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
	if(!_isStartPositionInitialized)
	{
		_startPosition = newPos;
		_isStartPositionInitialized = true;
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

const Vector2D& Ghost::GetVelocity() const
{
	return _velocity;
}

void Ghost::SetVelocity(const Vector2D& velocity)
{
	_velocity = velocity;
}

const Vector2D& Ghost::GetDirection() const
{
	return _direction;
}

void Ghost::SetDirection(const Vector2D& direction)
{
	_direction = direction;

	_velocity = _direction*_speed;
}

int Ghost::GetSpeed()
{
	return _speed;
}

void Ghost::OnPlayerPickedUpSuperBall(ICollidable&superBall)
{
	if (_currentState == State::BackToBase)
		return;

	_currentState = State::Scared;
	//Slow down and change color to blue
	_color = { 0,0,255,0 };

	_currentTexture = _eatableTextureName;

	_framesOffset = 0;

	_skipframesOffset = true;

	_isColorFlashing = false;

	_speed = 1;

	_velocity = _direction*_speed*(-1);
}

void Ghost::OnSuperBallSuperEnding()
{
	_isColorFlashing = true;
	_colorFlashingStart = clock();
	_tag = Tag::Enemy;
}

void Ghost::OnEndDurationsOfSuperBall()
{
	if (_currentState == State::BackToBase)
		return;

	_currentState = State::Normal;

	_color = _regularColor;
	
	_currentTexture = _textureName;

	_framesOffset = 0;

	_isColorFlashing = false;

	IncreaseVelocity();

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

	_color = { 255,255,255 };

	_currentTexture = _eyesTextureName;

	_framesOffset = 0;

	_skipframesOffset = true;

	IncreaseVelocity();

	_isEaten = true;

	_tag = Tag::Invulnerable;

	_currentState = State::BackToBase;
}

void Ghost::OnHitPlayer()
{
	SetupDefaultValues();
}

void Ghost::SetTextureName(const std::string& textureName)
{
	_currentTexture = _textureName = textureName;
}
