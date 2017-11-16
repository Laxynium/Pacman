#pragma once
#include "ILayerParser.h"
#include "IRenderer.h"
#include "ITextureManager.h"
#include "ICollisionManager.h"
#include "GameLogicHandler.h"
#include "Factory.h"

class ObjectLayerParser:public ILayerParser
{
	ICollisionManager& _collisionManager;
	GameLogicHandler & _gameLogicHandler;
	Factory& _factory;
public:
	ObjectLayerParser(ICollisionManager& collisionManager,GameLogicHandler &gameLogicHandler,Factory&factory);

	std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) override;
};
