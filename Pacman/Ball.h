#pragma once
#include "GameObject.h"
#include "ICollidable.h"
#include "ICollisionManager.h"

struct IRenderer;

class Ball:public GameObject,public ICollidable
{
	Tag _tag;
	bool IsPicked = false;
	Color _color = { 100,100,100,0 };
	ICollisionManager& _collisionManager;
public:
	Ball(IRenderer&renderer, ICollisionManager&collisionManager,const std::pair<int,int>&pos,int width, int height);
	
	void Draw() override;

	void Update() override;
	
	Rect GetAreaOfCollision() const override;
	
	Tag GetTag() const override;
	
	void OnCollsion(ICollidable& collidedObject) override;
	
	IRenderer& _renderer;
};
