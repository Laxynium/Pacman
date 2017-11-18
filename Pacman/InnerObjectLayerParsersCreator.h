#pragma once
#include <map>
#include "ObjectLayer.h"
#include "BallObjectLayerParser.h"
#include "IInnerObjectLayerParsersCreator.h"

class InnerObjectLayerParsersCreator:public IInnerObjectLayerParsersCreator
{
private:
	std::map<std::string, std::function<std::unique_ptr<IInnerObjectLayerParser>()>>_parsers;
	GameLogicHandler& _logicHandler;
	ICollisionManager& _collisionManager;
	Factory& _factory;
public:
	InnerObjectLayerParsersCreator(GameLogicHandler&logicHandler,Factory&factory,ICollisionManager&collisionManager): _logicHandler(logicHandler),
		_collisionManager(collisionManager), _factory(factory)
	{
		_parsers["Balls"] = [&]() {return std::make_unique<BallObjectLayerParser>(_logicHandler,_factory, _collisionManager); };
		/*	_parsers[""] = ;
		_parsers[""] = ;*/
	}

	std::unique_ptr<IInnerObjectLayerParser> Create(const std::string& type) override;

};
