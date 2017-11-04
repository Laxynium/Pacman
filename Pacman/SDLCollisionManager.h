#pragma once
#include "ICollisionManager.h"
class SDLCollisionManager :
	public ICollisionManager
{
protected:
	std::vector<ICollidable*>_objectsToDectection;

	static bool IsCollisionBetween(ICollidable* staticobject, ICollidable*  object);

public:
	 bool DetectCollision(ICollidable & object,Tag withWhat) override;

	 void Register(ICollidable & object) override;

};

