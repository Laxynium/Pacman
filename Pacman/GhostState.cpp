#include "GhostState.h"

void GhostState::Update()
{
	_animation.Update();
}

std::string GhostState::GetTextureName() const
{
	return _textureName;
}

void GhostState::SetTextureName(const std::string& textureName)
{
	_textureName = textureName;
}

int GhostState::GetSpeed() const
{
	return _speed;
}

void GhostState::SetSpeed(const int speed)
{
	_speed = speed;
}

Tag GhostState::GetTag() const
{
	return _tag;
}

void GhostState::SetTag(const Tag tag)
{
	_tag = tag;
}

Animation& GhostState::GetAnimation()
{
	return _animation;
}

void GhostState::SetAnimation(const Animation& animation)
{
	_animation = animation;
}
