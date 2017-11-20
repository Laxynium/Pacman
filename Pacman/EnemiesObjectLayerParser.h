#pragma once
#include "IInnerObjectLayerParser.h"
#include "Factory.h"

class EnemiesObjectLayerParser:public IInnerObjectLayerParser
{
	Factory& _factory;
	ICollisionManager& _collisionManager;
public:
	EnemiesObjectLayerParser(Factory&factory,ICollisionManager&collisionManager);
	std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) override;

};
