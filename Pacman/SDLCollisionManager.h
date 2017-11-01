#pragma once
#include "ICollisionManager.h"
class SDLCollisionManager :
	public ICollisionManager
{
protected:
	std::vector<ICollidable*>_objectsToDectection;

	static bool IsCollisionBetween(ICollidable* staticobject, ICollidable*  object);
public:
	virtual bool DetectCollision(ICollidable & object) override;

	virtual void Register(ICollidable & object) override;

};

