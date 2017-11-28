#pragma once
#include <vector>
#include "GameObject.h"
#include "MoveableGameObject.h"
#include "ICollidable.h"
#include <functional>
class ICollisionManager
{	
public:

	virtual void DetectAll() = 0;

	virtual bool DetectCollision(ICollidable &object,Tag withWhat) = 0;

	virtual void Register(ICollidable&object) = 0;

	//Subscribe to get notification if object with tag A collided with object with tag B
	virtual void Subscribe(Tag objectA,Tag objectB,std::function<void(ICollidable&,ICollidable&)>onCollison) = 0;

	virtual void Deregister(ICollidable&object) = 0;

	virtual void DeregisterAll() = 0;

	virtual ~ICollisionManager() {}
};

