#pragma once
#include "ILevelLoader.h"
#include "Tileset.h"
#include <vector>
#include "JsonParser.h"
#include "FromJsonLevelLoader.h"
#include "Layer.h"
#include "ITextureManager.h"
#include "ICollisionManager.h"

namespace Test
{
	struct Tileset;
	struct Layer;
}
class FromJsonLevelLoader:public ILevelLoader
{
	IRenderer &_renderer;
	ITextureManager &_textureManager;
	ICollisionManager& _collisionManager;
public:
	FromJsonLevelLoader(IRenderer&renderer, ITextureManager&textureManager,ICollisionManager&collisionManager);
	~FromJsonLevelLoader();

	std::unique_ptr<Level> LoadLevel(const std::string& fileName) override;

private:
	std::vector<Test::Tileset>ParseTilesets(nlohmann::basic_json<>json);
	std::vector<Test::Layer> ParseLayers(nlohmann::basic_json<> level_json);
};

