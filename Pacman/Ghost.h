#pragma once
#include "GameObject.h"
#include "IRenderer.h"
#include "ICollisionManager.h"
#include <ctime>

class Ghost:public GameObject,public ICollidable
{
	IRenderer& _renderer;
	ICollisionManager& _collisionManager;
	Color _regularColor = { 255,255,255,0 };
	Color _color = _regularColor;
	Tag _tag;
	Vector2D _vecToMove = {};
	int _timeOfBlueState = 8000;
	int _speed = 2;
	bool _isBlueState = false;
	void UpdateState();
	clock_t _startTime;
public:
	Ghost(IRenderer& renderer, ICollisionManager& collisionManager/*,IAiController controller*/);
	void Draw() override;
	void Update() override;

	Rect GetAreaOfCollision() const override;
	Tag GetTag() const override;
	void OnCollsion(ICollidable& collidedObject) override;

	void SetColor(const Color& color);

	void SetTag(Tag tag);

	void OnPlayerPickedUpSuperBall(ICollidable&superBall);

};
