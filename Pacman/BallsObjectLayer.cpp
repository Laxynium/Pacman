#include "BallsObjectLayer.h"
#include <algorithm>

BallsObjectLayer::BallsObjectLayer(const std::string& type): ObjectLayer(
	type)
{
}


void BallsObjectLayer::OnCollisionWithPlayer(ICollidable& objectA, ICollidable& objectB)
{
	auto &objectToDelete = (objectA.GetTag() != Tag::Player) ? objectA : objectB;

	RemoveObject(objectToDelete);

}

void BallsObjectLayer::OnCollisionSuperBallWithPlayer(ICollidable& objectA, ICollidable& objectB)
{
	//_gameLogicHandler.PlayerPickedUpSuperBall(objectA);

	auto &objectToDelete = (objectA.GetTag() != Tag::Player) ? objectA : objectB;

	RemoveObject(objectToDelete);
}

void BallsObjectLayer::RemoveObject(ICollidable& objectToDelete)
{
	auto toDelete = std::find_if(_gameObjects.begin(), _gameObjects.end(), [&](auto&object)
	{
		ICollidable * collidable = dynamic_cast<ICollidable*>(object.get());

		if (collidable == nullptr)return false;

		return collidable == &objectToDelete;
	});

	if (toDelete != _gameObjects.end())
		_gameObjects.erase(toDelete);
}

void BallsObjectLayer::SubscribeTo(ICollisionManager& collisionManager)
{
	collisionManager.Subscribe(Tag::Player, Tag::Pickable, [&](auto&objectA, auto&objectB)
	{
		OnCollisionWithPlayer(objectA, objectB);
	});
	collisionManager.Subscribe(Tag::Player, Tag::SuperBall, [&](auto&objectA, auto&objectB)
	{
		OnCollisionSuperBallWithPlayer(objectA, objectB);
	});
}

void BallsObjectLayer::Update()
{
	static bool hasEnded = false;
	if (_gameObjects.empty() && !hasEnded)
		;//_gameLogicHandler.GameEnded();

	for (auto&gameObject : _gameObjects)
		gameObject->Update();
}
