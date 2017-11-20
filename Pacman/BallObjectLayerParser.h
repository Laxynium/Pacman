#pragma once
#include "IInnerObjectLayerParser.h"
#include "Factory.h"
#include "GameLogicHandler.h"

class BallObjectLayerParser:public IInnerObjectLayerParser
{
	Factory& _factory;
	ICollisionManager& _collisionManager;
	GameLogicHandler& _gameLogicHandler;
public:
	BallObjectLayerParser(Factory&factory, ICollisionManager&collisionManager, GameLogicHandler&gameLogicHandler);

	std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) override;
	
};
