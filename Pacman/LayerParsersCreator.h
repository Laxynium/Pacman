#pragma once
#include <string>
#include "ILayerParser.h"
#include "ILayerParsersCreator.h"
#include "Tileset.h"
#include "GameLogicHandler.h"
#include "Factory.h"


class ICollisionManager;
struct IRenderer;
struct ITextureManager;

class LayerParsersCreator
{
	ITextureManager& _textureManager;
	IRenderer& _renderer;
	ICollisionManager& _collisionManager;
	std::unique_ptr<std::vector<Properties::Tileset>> _tilesets=nullptr;
	std::map<std::string, std::function<std::unique_ptr<ILayerParser>()>>_mappedParsers;
	GameLogicHandler& _gameLogicHandler;
	Factory &_factory;
public:
	LayerParsersCreator(ITextureManager&textureManager, IRenderer&renderer, ICollisionManager&collisionManager,GameLogicHandler&gameLogicHandler,Factory &factory);
	
	void AddTilesets(std::vector<Properties::Tileset>&&tilesets);

	std::unique_ptr<ILayerParser> Create(const std::string& type);

};
