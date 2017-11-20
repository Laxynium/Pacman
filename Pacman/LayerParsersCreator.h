#pragma once
#include <string>
#include "ILayerParser.h"
#include "Tileset.h"
#include "Factory.h"
#include "IInnerObjectLayerParsersCreator.h"


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
	Factory &_factory;
	IInnerObjectLayerParsersCreator& _innerObjectLayerParsersCreator;
public:
	LayerParsersCreator(ITextureManager&textureManager, IRenderer&renderer, ICollisionManager&collisionManager,Factory &factory
						, IInnerObjectLayerParsersCreator &innerObjectLayerParsersCreator);
	
	void AddTilesets(std::vector<Properties::Tileset>&&tilesets);

	std::unique_ptr<ILayerParser> Create(const std::string& type);

};
