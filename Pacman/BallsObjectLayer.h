#pragma once
#include "ObjectLayer.h"

class BallsObjectLayer:public ObjectLayer
{
protected:
	void OnCollisionWithPlayer(ICollidable&objectA, ICollidable&objectB);
	void OnCollisionSuperBallWithPlayer(ICollidable&objectA, ICollidable&objectB);
	void RemoveObject(ICollidable&objectToDelete);
public:
	BallsObjectLayer(const std::string& type);

	void SubscribeTo(ICollisionManager&collisionManager);

	void Update() override;

};
