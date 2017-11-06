#pragma once
#include "ILevelLoader.h"
#include "Tileset.h"
#include <vector>
#include "JsonParser.h"
#include "FromJsonLevelLoader.h"
#include "ITextureManager.h"
#include "ICollisionManager.h"
#include "ILayerParsersCreator.h"

namespace Test
{
	struct Tileset;
	class Layer;
}
class FromJsonLevelLoader:public ILevelLoader
{
	IRenderer &_renderer;
	ITextureManager &_textureManager;
	ICollisionManager& _collisionManager;
	LayerParsersCreator& _layerParsersCreator;
public:
	FromJsonLevelLoader(IRenderer&renderer, ITextureManager&textureManager,ICollisionManager&collisionManager, LayerParsersCreator&layerParsersCreator);

	std::unique_ptr<Level> LoadLevel(const std::string& fileName) override;

private:
	std::vector<Test::Tileset> ParseTilesets(nlohmann::basic_json<>json);
	std::vector<std::unique_ptr<LayerBase>> ParseLayers(nlohmann::basic_json<> level_json, std::vector<Test::Tileset>&&tilesets);
};

