#pragma once
#include "IInnerObjectLayerParser.h"
#include "Factory.h"

class BallObjectLayerParser:public IInnerObjectLayerParser
{
	Factory& _factory;
	ICollisionManager& _collisionManager;
public:
	BallObjectLayerParser(Factory&factory, ICollisionManager&collisionManager);

	std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) override;
	
};
