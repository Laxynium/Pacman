#pragma once
#include "IInnerObjectLayerParser.h"
#include "Factory.h"
#include "GameLogicHandler.h"

class EnemiesObjectLayerParser:public IInnerObjectLayerParser
{
	Factory& _factory;
	ICollisionManager& _collisionManager;
	GameLogicHandler& _gameLogicHandler;
public:
	EnemiesObjectLayerParser(Factory&factory,ICollisionManager&collisionManager, GameLogicHandler&gameLogicHandler);
	std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) override;

};
