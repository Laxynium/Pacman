#include "Ball.h"
#include "IRenderer.h"
Ball::Ball(IRenderer& renderer, const std::pair<int, int>&pos):_renderer(renderer)
{
	_tag = Tag::Pickable;
	_position = pos;
	_position.first += 10, _position.second += 10;
	_height = 12;
	_width = 12;
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

	if (IsPicked)
		return;

	IsPicked = true;

	_color = { 255, 255, 0, 0 };
}
