#pragma once
#include "GameObject.h"
#include "ICollidable.h"
#include "ICollisionManager.h"

struct IRenderer;

class Ball:public GameObject,public ICollidable
{
protected:
	Tag _tag;
	bool IsPicked = false;
	Color _color = { 255,255,0,255 };
	ICollisionManager& _collisionManager;
public:
	Ball(IRenderer&renderer, ICollisionManager&collisionManager,const Vector2D&pos,int width, int height);
	
	void Draw() override;

	void Update() override;
	
	Rect GetAreaOfCollision() const override;
	
	Tag GetTag() const override;
	
	void SetTag(const Tag& tag);

	IRenderer& _renderer;
};
