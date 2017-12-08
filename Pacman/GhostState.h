#pragma once
#include <string>
#include "Tag.h"
#include "Animation.h"

class GhostState:public IUpdateable
{
	std::string _textureName;
	int _speed=0;
	Tag _tag=Tag::Enemy;
	Animation _animation{1,20,0};
public:
	GhostState()
	{
	}

	GhostState(const std::string& textureName, int speed, Tag tag,
		const Animation& animation)
		: _textureName(textureName),  
		  _speed(speed),
		  _tag(tag),
		  _animation(animation)
	{
	}


	void Update() override;

	std::string GetTextureName() const;

	void SetTextureName(const std::string& textureName);

	int GetSpeed() const;

	void SetSpeed(const int speed);

	Tag GetTag() const;

	void SetTag(const Tag tag);

	Animation& GetAnimation();

	void SetAnimation(const Animation& animation);
};
