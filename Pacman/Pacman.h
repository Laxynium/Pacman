#pragma once
#include "IDrawable.h"
#include "IRenderer.h"
#include "MoveableGameObject.h"
#include "ICollisionManager.h"
#include "Color.h"
#include "ICollidable.h"
#include <ctime>

struct ITextureManager;

class Pacman:public MoveableGameObject,public ICollidable
{
private:
	IRenderer&_renderer;

	ICollisionManager& _collisionManager;

	ITextureManager& _textureManager;


	Vector2D _vecToMove;

	Color _color;

	Tag _tag;

	double _speed = 2;

	double _angle = 0;

	int _currentFrame = 1;

	int _framesCount = 3;

	int _columnsCount = 3;

	clock_t _animClock=0;

	int _animDelay = 60;//ms

	Vector2D _startPosition;

public:

	Pacman(IRenderer &renderer, ICollisionManager&collisionManager,ITextureManager&textureManager);

	void SetPosition(const Vector2D& newPos) override;

	void Draw() override;

	void Move(const Vector2D& vec) override;

	void Update() override;

	Rect GetAreaOfCollision()const override;

	Tag GetTag() const override;

	void OnBeingHit();

};

