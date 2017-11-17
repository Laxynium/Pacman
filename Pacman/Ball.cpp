#include "Ball.h"
#include "IRenderer.h"
#include <iostream>
#include "ICollisionManager.h"
#include "Vector2D.h"

Ball::Ball(IRenderer& renderer,ICollisionManager&collisionManager,const Vector2D&pos,int width,int height):_renderer(renderer), _collisionManager(collisionManager)
{
	_tag = Tag::Pickable;
	_position = pos;
	_width = width;
	_height = height;
	_position += Vector2D(16 - (width / 2), 16 - (height / 2));
}

void Ball::Draw()
{
	_renderer.FillRect(Rect {static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height,_color});
}

void Ball::Update()
{
}

Rect Ball::GetAreaOfCollision() const
{
	return Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height };
}

Tag Ball::GetTag() const
{
	return _tag;
}

void Ball::OnCollsion(ICollidable& collidedObject)
{
	if (collidedObject.GetTag() != Tag::Picker)
		return;

	//std::cout << "Ball collided\n";
	_collisionManager.Deregister(*this);
}
