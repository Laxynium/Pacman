#include "Ball.h"
#include "IRenderer.h"
#include <iostream>
#include "ICollisionManager.h"

Ball::Ball(IRenderer& renderer,ICollisionManager&collisionManager,const std::pair<int, int>&pos,int width,int height):_renderer(renderer), _collisionManager(collisionManager)
{
	_tag = Tag::Pickable;
	_position = pos;
	_width = width;
	_height = height;
	_position.first += (16-(width/2)), _position.second += (16-(height/2));
}

void Ball::Draw()
{
	_renderer.FillRect(Rect {_position.first,_position.second,_width,_height,_color});
}

void Ball::Update()
{
}

Rect Ball::GetAreaOfCollision() const
{
	return Rect{ _position.first,_position.second,_width,_height };
}

Tag Ball::GetTag() const
{
	return _tag;
}

void Ball::OnCollsion(ICollidable& collidedObject)
{
	if (collidedObject.GetTag() != Tag::Picker)
		return;

	std::cout << "Ball collided\n";

	_color = { 255, 255, 0, 0 };

	_collisionManager.Deregister(*this);
}
