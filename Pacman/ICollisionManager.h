#pragma once
#include <vector>
#include "GameObject.h"
#include "MoveableGameObject.h"
#include "ICollidable.h"

class ICollisionManager
{	
public:
	virtual bool DetectCollision(ICollidable &object,Tag withWhat) = 0;

	virtual void Register(ICollidable&object) = 0;

	virtual ~ICollisionManager() {}
};

