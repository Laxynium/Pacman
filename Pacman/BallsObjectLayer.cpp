#include "BallsObjectLayer.h"
#include <algorithm>

BallsObjectLayer::BallsObjectLayer(const std::string& type): ObjectLayer(
	type)
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
	static bool hasEnded = false;
	if (_gameObjects.empty() && !hasEnded)
		;//_gameLogicHandler.GameEnded();

	for (auto&gameObject : _gameObjects)
		gameObject->Update();
}
