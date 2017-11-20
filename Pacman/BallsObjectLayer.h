#pragma once
#include "ObjectLayer.h"

class BallsObjectLayer:public ObjectLayer
{
protected:
	void RemoveObject(ICollidable&objectToDelete);
public:

	BallsObjectLayer( BallsObjectLayer&) = delete;

	BallsObjectLayer(const std::string& type);


	void OnCollisionWithPlayer(ICollidable&objectA);

	void OnCollisionSuperBallWithPlayer(ICollidable&objectA);

	void Update() override;

};
