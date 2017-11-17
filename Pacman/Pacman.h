#pragma once
#include "IDrawable.h"
#include "IRenderer.h"
#include "MoveableGameObject.h"
#include "ICollisionManager.h"
#include "Color.h"
#include "ICollidable.h"

class Pacman:public MoveableGameObject,public ICollidable
{
private:
	IRenderer&_renderer;
	ICollisionManager& _collisionManager;
	Vector2D _vecToMove;
	Color _color;
	Tag _tag;
	double _speed = 2;

public:
	void Draw() override;
	void Move(const Vector2D& vec) override;
	void Update() override;
	Rect GetAreaOfCollision()const override;
	void OnCollsion(ICollidable& collidedObject) override;
	Tag GetTag() const override;
	Pacman(IRenderer &renderer,ICollisionManager&collisionManager);
	~Pacman();
};

