#pragma once
#include "GameObject.h"
#include "IRenderer.h"
#include "ICollisionManager.h"
#include <ctime>
#include "MoveToPositionBehaviour.h"
#include "IDestroyable.h"

class Ghost:public GameObject,public ICollidable
{
	enum class State
	{
		Base, Normal,BackToBase,Scared
	};
	State _currentState=State::Base;

	IRenderer& _renderer;

	ICollisionManager& _collisionManager;

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

	int _currentFrame = 1;

	int _framesCount = 3;

	int _columnsCount = 3;

private://methods
	void OnLeaveBase();

	void OnReturnToBase();

	void SetupBehaviours();

	void IncreaseVelocity();

	void SetupDefaultValues();

	void SetVelocity(const Vector2D& velocity);

public:
	Ghost(IRenderer& renderer, ICollisionManager& collisionManager/*,IAiController controller*/);

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

	
};
