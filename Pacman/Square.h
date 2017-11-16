#pragma once
#include "IDrawable.h"
#include "IRenderer.h"
#include "MoveableGameObject.h"
#include "ICollisionManager.h"
#include "Color.h"
#include "ICollidable.h"

class Square:public MoveableGameObject,public ICollidable
{
private:
	IRenderer&_renderer;
	ICollisionManager& _collisionManager;
	std::pair<int, int>_vecToMove;
	Color _color;
	Tag _tag;
	bool _collided = false;
	std::pair<int, int>_oldPosistion;
public:
	void Draw() override;
	void Move(const std::pair<int,int>& vec) override;
	void Update() override;
	Rect GetAreaOfCollision()const override;
	void OnCollsion(ICollidable& collidedObject) override;
	Tag GetTag() const override;
	Square(IRenderer &renderer,ICollisionManager&collisionManager);
	~Square();
};

