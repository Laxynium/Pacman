#pragma once
#include "ILayerParser.h"
#include "ITextureManager.h"
#include "IRenderer.h"
#include "ICollisionManager.h"
#include "Tileset.h"
#include "Factory.h"

class TileLayerParser:public ILayerParser
{
	ICollisionManager& _collisionManager;
	std::vector<Properties::Tileset>& _tilesets;
	Factory& _factory;
public:
	TileLayerParser(ICollisionManager&collisonManager, 
		std::vector<Properties::Tileset>& tilesets, Factory &factory);

	std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) override;
};
