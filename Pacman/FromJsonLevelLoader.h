#pragma once
#include "ILevelLoader.h"
#include "Tileset.h"
#include <vector>
#include "JsonParser.h"
#include "FromJsonLevelLoader.h"
#include "ITextureManager.h"
#include "LayerParsersCreator.h"

namespace Properties
{
	struct Tileset;
	class Layer;
}
class FromJsonLevelLoader:public ILevelLoader
{
	ITextureManager &_textureManager;
	LayerParsersCreator& _layerParsersCreator;
	Factory& _factory;
public:
	FromJsonLevelLoader( ITextureManager&textureManager, LayerParsersCreator&layerParsersCreator,Factory&factory);

	std::unique_ptr<Level> LoadLevel(const std::string& fileName) override;

private:
	std::vector<Properties::Tileset> ParseTilesets(nlohmann::basic_json<>json);
	std::vector<std::unique_ptr<LayerBase>> ParseLayers(nlohmann::basic_json<> level_json, std::vector<Properties::Tileset>&&tilesets);
};

