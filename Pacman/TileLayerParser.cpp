#include "TileLayerParser.h"
#include "TileLayer.h"
using nlohmann::json;
namespace Test
{
	void from_json(const json& layerJson, Test::LayerProperties& p) {
		auto data = layerJson.at("data").get<std::vector<int>>();
		p.Height = layerJson.at("height").get<int>();
		p.Width = layerJson.at("width").get<int>();
		p.X = layerJson.at("x").get<int>();
		p.Y = layerJson.at("y").get<int>();
		p.Name = layerJson.at("name").get<std::string>();
		p.SetData(data);
		p.IsCollidable = layerJson.at("properties").at("collidable").get<bool>();
	}
}

TileLayerParser::TileLayerParser(ITextureManager& textureManager, IRenderer& renderer,
	ICollisionManager& collisonManager, std::vector<Test::Tileset>& tilesets)
	:_textureManager(textureManager),_renderer(renderer),_collisionManager(collisonManager), _tilesets(tilesets)
{
}

std::unique_ptr<LayerBase> TileLayerParser::Parse(nlohmann::basic_json<> json)
{
	auto type = json.at("type").get<std::string>();
	auto tileLayer = std::make_unique<Test::TileLayer>(type,_textureManager, _renderer);

	const Test::LayerProperties layerProp = json;

	tileLayer->SetProperties(layerProp);

	tileLayer->Properties().SetTilesets(_tilesets);

	tileLayer->GenerateTiles();

	if (!tileLayer->Properties().IsCollidable)
		return tileLayer;

	for (auto*tile : tileLayer->GetTiles())
		_collisionManager.Register(*tile);

	return tileLayer;
}
