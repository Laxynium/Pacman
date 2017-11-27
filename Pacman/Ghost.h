#pragma once
#include "GameObject.h"
#include "IRenderer.h"
#include "ICollisionManager.h"
#include <ctime>
#include "MoveToPositionBehaviour.h"

class Ghost:public GameObject,public ICollidable
{
	IRenderer& _renderer;

	ICollisionManager& _collisionManager;

	Color _regularColor = { 255,255,255,0 };

	Color _color = _regularColor;

	Tag _tag;

	Vector2D _velocity = {};

	int _speed = 2;

	Vector2D _startPosition = {};

	BehaviourBase * _currentBehaviour;

	std::vector<std::unique_ptr<BehaviourBase>>_behaviours;

	bool _initialized=false;

	int _counter=0;

	bool _isEaten = false;

	void LeftBaseCallback();

	void ReturnedToBaseCallback();

public:
	Ghost(IRenderer& renderer, ICollisionManager& collisionManager/*,IAiController controller*/);

	void Draw() override;

	void Update() override;

	Rect GetAreaOfCollision() const override;

	Tag GetTag() const override;

	void SetPosition(const Vector2D& newPos) override;

	void SetColor(const Color& color);

	void SetTag(Tag tag);


	Vector2D& GetVelocity()
	{
		return _velocity;
	}

	void SetVelocity(const Vector2D& velocity)
	{
		_velocity = velocity;
	}

	int GetSpeed();

	void OnPlayerPickedUpSuperBall(ICollidable&superBall);

	void OnEndDurationsOfSuperBall();

	void OnBeingAte(ICollidable&ghost);

	void OnHitPlayer();

	
};
