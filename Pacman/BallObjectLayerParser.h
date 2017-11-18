#pragma once
#include "IInnerObjectLayerParser.h"
#include "Factory.h"

class BallObjectLayerParser:public IInnerObjectLayerParser
{
public:
	BallObjectLayerParser(GameLogicHandler& gameLogicHandler,Factory&factory, ICollisionManager&collisionManager);

	std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) override;
	GameLogicHandler& _gameLogicHandler;
	Factory& _factory;
	ICollisionManager& _collisionManager;
};
