#include "ObjectLayer.h"
#include <algorithm>
#include <iostream>


void ObjectLayer::OnCollisionBetweenPickerAndPickable(ICollidable& objectA, ICollidable& objectB)
{
	auto &objectToDelete = objectA.GetTag() == Tag::Pickable ? objectA : objectB;

	auto toDelete=std::find_if(_gameObjects.begin(),_gameObjects.end(),[&](auto&object)
	{
		ICollidable * collidable = dynamic_cast<ICollidable*>(object.get());

		if (collidable == nullptr)return false;

		return collidable == &objectToDelete;
	});

	if (toDelete != _gameObjects.end())
		_gameObjects.erase(toDelete);

}

ObjectLayer::ObjectLayer(const std::string& type, GameLogicHandler&gameLogicHandler): LayerBase(type), _gameLogicHandler(gameLogicHandler)
{
}

void ObjectLayer::Draw()
{
	for (auto&gameObject : _gameObjects)
		gameObject->Draw();
}

ObjectLayer::~ObjectLayer()
{
}

const std::unique_ptr<Properties::ObjectLayerProperties>& ObjectLayer::Properties() const
{
	return _properties;
}

void ObjectLayer::SetProperties(Properties::ObjectLayerProperties&& object_layer_properties)
{
	_properties = std::make_unique<Properties::ObjectLayerProperties>(std::move(object_layer_properties));
}

std::vector<std::shared_ptr<GameObject>>& ObjectLayer::GameObjects()
{
	return _gameObjects;
}

void ObjectLayer::SetGameObjects(const std::vector<std::shared_ptr<GameObject>>& sharedPtrs)
{
	_gameObjects = sharedPtrs;
}

void ObjectLayer::SubscribeTo(ICollisionManager& collisionManager)
{
	collisionManager.Subscribe(Tag::Picker, Tag::Pickable, [&](auto&objectA, auto&objectB)
	{
		OnCollisionBetweenPickerAndPickable(objectA, objectB);
	});
}

void ObjectLayer::Update()
{
	static bool hasEnded = false;
	if (_gameObjects.empty()&&!hasEnded)
		_gameLogicHandler.GameEnded();

	for (auto&gameObject : _gameObjects)
		gameObject->Update();
}
