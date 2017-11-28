#include "BallsObjectLayer.h"
#include <algorithm>
#include <iostream>

BallsObjectLayer::BallsObjectLayer(const std::string& type, ICollisionManager&collisionManager): ObjectLayer(
	type,collisionManager)
{
}


void BallsObjectLayer::OnCollisionWithPlayer(ICollidable& objectA)
{
	RemoveObject(objectA);
}


void BallsObjectLayer::OnCollisionSuperBallWithPlayer(ICollidable& objectA)
{
	RemoveObject(objectA);
}

void BallsObjectLayer::RemoveObject(ICollidable& objectToDelete)
{
	if (_gameObjects.empty())return;

	auto toDelete = std::find_if(_gameObjects.begin(), _gameObjects.end(), [&](auto&object)
	{

		ICollidable * collidable = dynamic_cast<ICollidable*>(object.get());

		if (collidable == nullptr)return false;

		return collidable == &objectToDelete;
	});

	if (toDelete != _gameObjects.end())
		_gameObjects.erase(toDelete);
}


void BallsObjectLayer::Update()
{
	for (auto&gameObject : _gameObjects)
		gameObject->Update();
}
