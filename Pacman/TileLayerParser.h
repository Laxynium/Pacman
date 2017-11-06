#pragma once
#include "ILayerParser.h"
#include "ITextureManager.h"
#include "IRenderer.h"
#include "ICollisionManager.h"
#include "Tileset.h"

class TileLayerParser:public ILayerParser
{
	ICollisionManager& _collisionManager;
	IRenderer& _renderer;
	ITextureManager& _textureManager;
	std::vector<Test::Tileset>& _tilesets;
public:
	TileLayerParser(ITextureManager&textureManager, IRenderer&renderer, ICollisionManager&collisonManager, std::vector<Test::Tileset>& tilesets);

	std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) override;
};
