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
public:
	InnerObjectLayerParsersCreator(Factory&factory,ICollisionManager&collisionManager):
		_collisionManager(collisionManager), _factory(factory)
	{
		_parsers["Balls"] = [&]() {return std::make_unique<BallObjectLayerParser>(_factory, _collisionManager); };
		_parsers["Ghosts"] = [&]() {return std::make_unique<EnemiesObjectLayerParser>(_factory, _collisionManager); };
	}

	std::unique_ptr<IInnerObjectLayerParser> Create(const std::string& type) override;

};
