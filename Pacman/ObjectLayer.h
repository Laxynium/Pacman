#pragma once
#include "LayerBase.h"
#include "ObjectLayerProperties.h"
#include "ICollisionManager.h"
#include "GameLogicHandler.h"

class ObjectLayer:public LayerBase
{
	std::unique_ptr<Properties::ObjectLayerProperties>_properties;

	std::vector<std::shared_ptr<GameObject>>_gameObjects;
	GameLogicHandler& _gameLogicHandler;

	void OnCollisionBetweenPickerAndPickable(ICollidable&objectA, ICollidable&objectB);

public:
	explicit ObjectLayer(const std::string& type,GameLogicHandler&gameLogicHandler);

	~ObjectLayer();

	void Draw() override;

	const std::unique_ptr<Properties::ObjectLayerProperties>& Properties() const;

	void SetProperties(Properties::ObjectLayerProperties&& object_layer_properties);


	std::vector<std::shared_ptr<GameObject>>& GameObjects();

	void SetGameObjects(const std::vector<std::shared_ptr<GameObject>>& sharedPtrs);

	void SubscribeTo(ICollisionManager&collisionManager);

	void Update() override;
};

