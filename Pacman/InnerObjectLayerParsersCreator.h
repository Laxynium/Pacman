#pragma once
#include <map>
#include "ObjectLayer.h"
#include "BallObjectLayerParser.h"
#include "IInnerObjectLayerParsersCreator.h"
#include "EnemiesObjectLayerParser.h"

class InnerObjectLayerParsersCreator:public IInnerObjectLayerParsersCreator
{
private:
	std::map<std::string, std::function<std::unique_ptr<IInnerObjectLayerParser>()>>_parsers;
	ICollisionManager& _collisionManager;
	Factory& _factory;
	GameLogicHandler& _gameLogicHandler;
public:
	InnerObjectLayerParsersCreator(Factory& factory, ICollisionManager& collisionManager,GameLogicHandler&gameLogicHandler);

	std::unique_ptr<IInnerObjectLayerParser> Create(const std::string& type) override;

};
