#include "ObjectLayer.h"
#include "BallsObjectLayer.h"


ObjectLayer::ObjectLayer(const std::string& type): LayerBase(type)
{
}

void ObjectLayer::SetGameObjects(const std::vector<std::shared_ptr<GameObject>>& sharedPtrs)
{
	_gameObjects = sharedPtrs;
}

std::vector<std::shared_ptr<GameObject>>& ObjectLayer::GameObjects()
{
	return _gameObjects;
}

void ObjectLayer::Draw()
{
	for (auto&gameObject : _gameObjects)
		gameObject->Draw();
}

ObjectLayer::~ObjectLayer()
{
}

void ObjectLayer::Update()
{
	for (auto&gameObject : _gameObjects)
		gameObject->Update();
}
