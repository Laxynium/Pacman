#pragma once
#include "ObjectLayer.h"

class EnemiesObjectLayer:public ObjectLayer
{
public:
	EnemiesObjectLayer(const std::string& type,ICollisionManager&collisionManager);
};
