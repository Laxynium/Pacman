#include "ObjectLayer.h"


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

void ObjectLayer::Update()
{
	for (auto&gameObject : _gameObjects)
		gameObject->Update();
}
