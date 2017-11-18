#pragma once
#include "GameObject.h"
#include "IRenderer.h"
#include "ICollisionManager.h"

class Ghost:public GameObject,public ICollidable
{
	IRenderer& _renderer;
	ICollisionManager& _collisionManager;
	Color _color={255,255,255,0};
	Tag _tag;
	Vector2D _vecToMove = {};
public:
	Ghost(IRenderer& renderer, ICollisionManager& collisionManager/*,IAiController controller*/);
	void Draw() override;
	void Update() override;

	Rect GetAreaOfCollision() const override;
	Tag GetTag() const override;
	void OnCollsion(ICollidable& collidedObject) override;

	void SetColor(const Color& color);
};
