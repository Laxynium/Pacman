#pragma once
#include "LayerBase.h"
#include "ObjectLayerProperties.h"
#include "ICollisionManager.h"
#include "GameLogicHandler.h"

class ObjectLayer:public LayerBase
{
protected:

	std::vector<std::shared_ptr<GameObject>>_gameObjects;
	GameLogicHandler& _gameLogicHandler;

public:
	 ObjectLayer(const std::string& type,GameLogicHandler&gameLogicHandler);

	~ObjectLayer();

	void Draw() override;

	void Update() override;
};

