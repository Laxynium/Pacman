#pragma once
#include <string>
#include "ILayerParser.h"
#include "ILayerParsersCreator.h"
#include "Tileset.h"


class ICollisionManager;
struct IRenderer;
struct ITextureManager;

class LayerParsersCreator
{
	ITextureManager& _textureManager;
	IRenderer& _renderer;
	ICollisionManager& _collisionManager;
	std::unique_ptr<std::vector<Test::Tileset>> _tilesets=nullptr;
	std::map<std::string, std::function<std::unique_ptr<ILayerParser>()>>_mappedParsers;
public:
	LayerParsersCreator(ITextureManager&textureManager, IRenderer&renderer, ICollisionManager&collisionManager);
	
	void AddTilesets(std::vector<Test::Tileset>&&tilesets);

	std::unique_ptr<ILayerParser> Create(const std::string& type);

};
