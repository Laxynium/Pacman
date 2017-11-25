#pragma once
#include "ICollisionManager.h"

class Ghost;

class BehaviourBase:public IUpdateable
{
protected:
	Ghost *_ghost=nullptr;
	ICollisionManager&_collisionManager;
	virtual void OnTransition(Vector2D position);
public:
	BehaviourBase(ICollisionManager& collisionManager);
	
	virtual void SetControlledGhost(Ghost*ghost);
};
