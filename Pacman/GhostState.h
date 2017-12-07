#pragma once
#include <string>
#include "Tag.h"
#include "Animation.h"

class GhostState
{
	std::string _textureName;
	int _frameCount;
	int _columnsCount;
	int _speed;
	Tag _tag;
	Animation _animation;
public:
	GhostState(const std::string& textureName, int frameCount, int columnsCount, int speed, Tag tag,
		int animDelay)
		: _textureName(textureName),
		  _frameCount(frameCount),
		  _columnsCount(columnsCount),
		  _speed(speed),
		  _tag(tag),
		  _animation(frameCount, animDelay)
	{
	}
};
