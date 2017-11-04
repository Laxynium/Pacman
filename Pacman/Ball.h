#pragma once
#include "GameObject.h"
#include "ICollidable.h"

struct IRenderer;

class Ball:public GameObject,public ICollidable
{
	Tag _tag;
	bool IsPicked = false;
	Color _color = { 100,100,100,0 };
public:
	Ball(IRenderer&renderer,const std::pair<int,int>&pos);
	void Draw() override;
	void Update() override;
	Rect GetAreaOfCollision() const override;
	Tag GetTag() const override;
	void OnCollsion(ICollidable& collidedObject) override;
	IRenderer& _renderer;
};
