#include "ObjectLayer.h"
#include "BallsObjectLayer.h"


ObjectLayer::ObjectLayer(const std::string& type, ICollisionManager&collisionManager): LayerBase(type), _collisionManager(collisionManager)
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
	for (auto&gameObject : _gameObjects)
	{
		auto collidable = dynamic_cast<ICollidable*>(gameObject.get());

		if(collidable!=nullptr)
		{
			_collisionManager.Deregister(*collidable);
		}
	}		
}

void ObjectLayer::Update()
{
	for (auto&gameObject : _gameObjects)
		gameObject->Update();
}
