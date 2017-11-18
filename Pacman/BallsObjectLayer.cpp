#include "BallsObjectLayer.h"
#include <algorithm>

BallsObjectLayer::BallsObjectLayer(const std::string& type, GameLogicHandler& gameLogicHandler): ObjectLayer(
	type, gameLogicHandler)
{
}


void BallsObjectLayer::OnCollisionBetweenPickerAndPickable(ICollidable& objectA, ICollidable& objectB)
{
	auto &objectToDelete = objectA.GetTag() == Tag::Pickable ? objectA : objectB;

	auto toDelete = std::find_if(_gameObjects.begin(), _gameObjects.end(), [&](auto&object)
	{
		ICollidable * collidable = dynamic_cast<ICollidable*>(object.get());

		if (collidable == nullptr)return false;

		return collidable == &objectToDelete;
	});

	if (toDelete != _gameObjects.end())
		_gameObjects.erase(toDelete);

}

const std::unique_ptr<Properties::ObjectLayerProperties>& BallsObjectLayer::Properties() const
{
	return _properties;
}

void BallsObjectLayer::SetProperties(Properties::ObjectLayerProperties&& object_layer_properties)
{
	_properties = std::make_unique<Properties::ObjectLayerProperties>(std::move(object_layer_properties));
}

std::vector<std::shared_ptr<GameObject>>& BallsObjectLayer::GameObjects()
{
	return _gameObjects;
}

void BallsObjectLayer::SetGameObjects(const std::vector<std::shared_ptr<GameObject>>& sharedPtrs)
{
	_gameObjects = sharedPtrs;
}

void BallsObjectLayer::SubscribeTo(ICollisionManager& collisionManager)
{
	collisionManager.Subscribe(Tag::Picker, Tag::Pickable, [&](auto&objectA, auto&objectB)
	{
		OnCollisionBetweenPickerAndPickable(objectA, objectB);
	});
}

void BallsObjectLayer::Update()
{
	static bool hasEnded = false;
	if (_gameObjects.empty() && !hasEnded)
		_gameLogicHandler.GameEnded();

	for (auto&gameObject : _gameObjects)
		gameObject->Update();
}
