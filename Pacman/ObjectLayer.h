#pragma once
#include "LayerBase.h"
#include "ICollisionManager.h"
#include <memory>

class ObjectLayer:public LayerBase
{
protected:

	std::vector<std::shared_ptr<GameObject>>_gameObjects;
	ICollisionManager& _collisionManager;

public:
	 ObjectLayer(const std::string& type, ICollisionManager&collisionManager);

	~ObjectLayer();

	void SetGameObjects(const std::vector<std::shared_ptr<GameObject>>& sharedPtrs);

	std::vector<std::shared_ptr<GameObject>>& GameObjects();

	void Draw() override;

	void Update() override;
};

