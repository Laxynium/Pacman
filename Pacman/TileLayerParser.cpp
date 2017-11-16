#include "TileLayerParser.h"
#include "TileLayer.h"
#include "Factory.h"
using nlohmann::json;
namespace Properties
{
	void from_json(const json& layerJson, Properties::TileLayerProperties& p) {
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

TileLayerParser::TileLayerParser(ICollisionManager& collisonManager, std::vector<Properties::Tileset>& tilesets,Factory &factory)
	:_collisionManager(collisonManager), _tilesets(tilesets), _factory(factory)
{
}

std::unique_ptr<LayerBase> TileLayerParser::Parse(nlohmann::basic_json<> json)
{
	auto type = json.at("type").get<std::string>();

	std::unique_ptr<Properties::TileLayer> tileLayer(_factory.CreateTileLayer(type));

	const Properties::TileLayerProperties layerProp = json;

	tileLayer->SetProperties(std::move(layerProp));

	tileLayer->Properties().SetTilesets(_tilesets);

	tileLayer->GenerateTiles();

	if (!tileLayer->Properties().IsCollidable)
		return tileLayer;

	for (auto*tile : tileLayer->GetTiles())
		_collisionManager.Register(*tile);

	return tileLayer;
}
