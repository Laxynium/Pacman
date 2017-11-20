#pragma once
#include "ILayerParser.h"
#include "IRenderer.h"
#include "ITextureManager.h"
#include "ICollisionManager.h"
#include "Factory.h"
#include "IInnerObjectLayerParsersCreator.h"

class ObjectLayerParser:public ILayerParser
{
	ICollisionManager& _collisionManager;
	Factory& _factory;
	IInnerObjectLayerParsersCreator& _objectLayerParsersCreator;
public:
	ObjectLayerParser(ICollisionManager& collisionManager,Factory&factory,IInnerObjectLayerParsersCreator&objectLayerParsersCreator);

	std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) override;
};
