#pragma once
#include "GameObject.h"
#include "IRenderer.h"
#include "ICollisionManager.h"
#include <ctime>
#include "MoveToPositionBehaviour.h"
#include "IDestroyable.h"
#include "ITextureManager.h"

class Ghost:public GameObject,public ICollidable
{
	enum class State
	{
		Base, Normal,BackToBase,Scared
	};
	State _currentState=State::Base;

	IRenderer& _renderer;

	ICollisionManager& _collisionManager;

	ITextureManager& _textureManager;


	Color _regularColor = { 255,255,255,0 };

	Color _color = _regularColor;

	Tag _tag=Tag::Enemy;

	Vector2D _direction = { 1,0 };

	int _speed = 2;

	Vector2D _velocity = {};

	Vector2D _startPosition = {};

	BehaviourBase * _currentBehaviour;

	std::vector<std::unique_ptr<BehaviourBase>>_behaviours;

	bool _isStartPositionInitialized=false;

	bool _isColorFlashing = false;

	clock_t _colorFlashingStart = 0;

	Color _tempColor = { 0,0,255,0 };

	bool _isEaten = false;

	double _angle = 0;

	int _framesOffset = 0;
	bool _skipframesOffset = false;

	clock_t _animClock = 0;
	
	int _animDelay = 40;

	
	std::string _eyesTextureName;
	std::string _whiteTextureName;
	std::string _eatableTextureName;

	std::string _currentTexture;

private://methods
	void OnLeaveBase();

	void OnReturnToBase();

	void SetupBehaviours();

	void IncreaseVelocity();

	void SetupDefaultValues();

	void SetVelocity(const Vector2D& velocity);

public:
	Ghost(IRenderer& renderer, ICollisionManager& collisionManager,ITextureManager&textureManager);

	void Draw() override;

	void Update() override;

	Rect GetAreaOfCollision() const override;

	Tag GetTag() const override;

	void SetPosition(const Vector2D& newPos) override;

	void SetColor(const Color& color);

	void SetTag(Tag tag);


	const Vector2D& GetVelocity() const;

	const Vector2D& GetDirection() const;

	void SetDirection(const Vector2D& direction);

	int GetSpeed();

	void OnPlayerPickedUpSuperBall(ICollidable&superBall);
	void OnSuperBallSuperEnding();

	void OnEndDurationsOfSuperBall();

	void OnBeingAte(ICollidable&ghost);

	void OnHitPlayer();


	void SetEyesTextureName(const std::string& eyesTextureName)
	{
		_eyesTextureName = eyesTextureName;
	}

	void SetWhiteTextureName(const std::string& whiteTextureName)
	{
		_whiteTextureName = whiteTextureName;
	}

	void SetEatableTextureName(const std::string& eatableTextureName)
	{
		_eatableTextureName = eatableTextureName;
	}
	void SetTextureName(const std::string& textureName) override;
};
