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
	//0
	auto leaveBaseBehaviour = std::make_unique<MoveToPositionBehaviour>(_collisionManager);
	leaveBaseBehaviour->SetControlledGhost(this);
	leaveBaseBehaviour->SetDestination({ 448,352 });
	leaveBaseBehaviour->ReachedToDestination += std::bind(&Ghost::OnLeaveBase, this);
	_behaviours.emplace_back(std::move(leaveBaseBehaviour));

	//1
	auto randomBehaviour = std::make_unique<RandomBehaviour>(_collisionManager);
	randomBehaviour->SetControlledGhost(this);
	_behaviours.emplace_back(std::move(randomBehaviour));

	//2
	auto returnToBaseBehaviour = std::make_unique<MoveToPositionBehaviour>(_collisionManager);
	returnToBaseBehaviour->SetControlledGhost(this);
	returnToBaseBehaviour->SetDestination({ 448,384 });
	returnToBaseBehaviour->ReachedToDestination += std::bind(&Ghost::OnReturnToBase, this);
	_behaviours.emplace_back(std::move(returnToBaseBehaviour));

	_currentBehaviour = _behaviours[0].get();
}

void Ghost::OnStateChanged()
{
	switch (_currentState)
	{
	case State::Base:
		_tag = Tag::Enemy;
		_currentTexture = _textureName;
		_framesOffset= 0;
		_animation.SetFrameOffset(0);
		_framesCount = 2;
		_animation.SetFrameCount(2);
		_columnsCount = 2;
		_animation.SetColumnsCount(2);
		_currentFrame = 0;
		_animation.SetCurrentFrame(0);
		IncreaseVelocity();
		_velocity = _direction*_speed;
		break;
	case State::Normal:
		_tag = Tag::Enemy;
		_currentTexture = _textureName;
		_framesOffset = 0;
		_animation.SetFrameOffset(0);
		_framesCount = 2;
		_animation.SetFrameCount(2);
		_columnsCount = 2;
		_animation.SetColumnsCount(2);
		_currentFrame = 0;
		_animation.SetCurrentFrame(0);
		IncreaseVelocity();
		_velocity = _direction*_speed;
		break;
	case State::Scared:
		_tag = Tag::Frightened;
		_currentTexture = _eatableTextureName;
		_framesOffset = 0;
		_animation.SetFrameOffset(0);
		_framesCount = 2;
		_animation.SetFrameCount(2);
		_columnsCount = 2;
		_animation.SetColumnsCount(2);
		_currentFrame = 0;
		_animation.SetCurrentFrame(0);
		_speed = 1;
		_velocity = _direction*_speed*(-1);
		break;
	case State::BackToBase:
		_tag = Tag::Invulnerable;
		_currentTexture = _eyesTextureName;
		_framesOffset = 0;
		_animation.SetFrameOffset(0);
		_framesCount = 1;
		_animation.SetFrameCount(1);
		_columnsCount = 1;
		_animation.SetColumnsCount(1);
		_currentFrame = 0;
		_animation.SetCurrentFrame(0);
		IncreaseVelocity();
		_velocity = _direction*_speed;
		break;
	case State::Flashing:
		break;
	}
}

void Ghost::Draw()
{
	int x = ((_currentFrame % _columnsCount)+ _framesOffset)*(_width);
	int y = ((_currentFrame) / _columnsCount) * _height;

	_renderer.CopyEx(_textureManager.FindTexture(_currentTexture), &Rect{ x,y,_width,_height }, &Rect{ static_cast<int>(_position.X()),
		static_cast<int>(_position.Y()),_width,_height });
}

Rect Ghost::GetAreaOfCollision() const
{
	//x,y,w,h,color
	return Rect{ static_cast<int>(_position.X()),
		static_cast<int>(_position.Y()),_width,_height };
}

void Ghost::SetupDefaultValues()
{
	_position = _startPosition;

	if (_behaviours.empty())
		return;

	_currentBehaviour = _behaviours[0].get();

	_currentTexture = _textureName;

	_framesOffset = 0;

	_animation.SetCurrentFrame(0);
	_animation.SetFrameCount(2);
	_animation.SetFrameOffset(0);

	_tag = Tag::Enemy;

	_currentState = State::Base;

	_speed = 2;

	_velocity = _direction*_speed;
}


void Ghost::Update()
{
	_currentBehaviour->Update();

	auto updateFrameOffset=[this](int n)
	{
		if (_direction.X() > 0)
			_animation.SetFrameOffset(0);
		else if (_direction.X() < 0)
			_animation.SetFrameOffset(n*1);
		else if (_direction.Y() < 0)
			_animation.SetFrameOffset(n*2);
		else if (_direction.Y() > 0)
			_animation.SetFrameOffset(n*3);
	};

	switch(_currentState)
	{
		case State::Base:
			updateFrameOffset(2);
			break;
		case State::Normal:
			updateFrameOffset(2);
			break;
		case State::Scared:
			break;
		case State::BackToBase:
			updateFrameOffset(1);
			break;
		case State::Flashing:
			clock_t currentTime = clock();
			if(currentTime-_changeTextureClock>=60)
			{
				if (_currentTexture == _eatableTextureName)
					_currentTexture = _whiteTextureName;
				else
					_currentTexture = _eatableTextureName;

					_changeTextureClock = currentTime;
			}
			break;
	}
	_animation.Update();
	_currentFrame = _animation.GetCurrentFrame();
	_framesOffset = _animation.GetFrameOffset();
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
	//Change to random behaviour
	_currentBehaviour = this->_behaviours[1].get();

	_currentState = State::Normal;
	OnStateChanged();
}
void Ghost::OnReturnToBase()
{
	_currentState = State::Base;
	_currentBehaviour = _behaviours[0].get();
	OnStateChanged();
}


void Ghost::OnPlayerPickedUpSuperBall(ICollidable&superBall)
{
	if (_currentState == State::BackToBase)return;

	_currentState = State::Scared;

	OnStateChanged();
}

void Ghost::OnSuperBallPowerEnding()
{
	if (_currentState == State::BackToBase||_currentState==State::Normal||_currentState==State::Base)return;

	_currentState = State::Flashing;

	//OnStateChanged();
}

void Ghost::OnEndDurationsOfSuperBall()
{
	if (_currentState == State::BackToBase)return;

	_currentState = State::Normal;
	
	OnStateChanged();
}

void Ghost::OnBeingEaten(ICollidable&ghost)
{
	if (&ghost != this)return;

	_currentState = State::BackToBase;
	_currentBehaviour = _behaviours[2].get();
	OnStateChanged();
}

void Ghost::OnHitPlayer()
{
	SetupDefaultValues();
}


//Setters and Getters

void Ghost::SetEyesTextureName(const std::string& eyesTextureName)
{
	_eyesTextureName = eyesTextureName;
}

void Ghost::SetWhiteTextureName(const std::string& whiteTextureName)
{
	_whiteTextureName = whiteTextureName;
}

void Ghost::SetEatableTextureName(const std::string& eatableTextureName)
{
	_eatableTextureName = eatableTextureName;
}

void Ghost::SetTextureName(const std::string& textureName)
{
	_currentTexture = _textureName = textureName;
}

Tag Ghost::GetTag() const
{
	return _tag;
}


void Ghost::SetPosition(const Vector2D& newPos)
{
	GameObject::SetPosition(newPos);
	if (!_isStartPositionInitialized)
	{
		_startPosition = newPos;
		_isStartPositionInitialized = true;
	}
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

