#pragma once
#include "IUpdateable.h"
#include "ICollisionManager.h"
#include "BehaviourBase.h"

class RandomBehaviour:public BehaviourBase
{
public:
	RandomBehaviour(ICollisionManager&collisionManager):BehaviourBase(collisionManager) {  }
	void Update() override;
};
