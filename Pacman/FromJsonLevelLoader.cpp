#include "FromJsonLevelLoader.h"
#include "JsonParser.h"
#include "Tileset.h"
#include <fstream>
using namespace std;
using nlohmann::json;

namespace Properties {
	void from_json(const json& j, Tileset& p) {
		p.Columns = j.at("columns").get<int>();
		p.TileCount = j.at("tilecount").get<int>();
		p.Rows = p.TileCount / p.Columns;
		p.ImageSource = j.at("image").get<std::string>();
		p.ImageWidth = j.at("imagewidth").get<int>();
		p.ImageHeight = j.at("imageheight").get<int>();
		
		p.TileWidth = j.at("tilewidth").get<int>();
		p.TileHeight = j.at("tileheight").get<int>();
		p.Margin = j.at("margin").get<int>();
		p.Spacing = j.at("spacing").get<int>();
		p.Name = j.at("name").get<std::string>();
	}
}

std::unique_ptr<Level> FromJsonLevelLoader::LoadLevel(const std::string& fileName)
{
	std::ifstream jsonFileStream(fileName);

	if(!jsonFileStream.good())
	{	
		throw std::exception("Couldn't open file.");
	}

	const auto levelJson=json::parse(jsonFileStream);

	auto tilesets = ParseTilesets(levelJson);

	auto layers = std::move(ParseLayers(levelJson,std::move(tilesets)));

	std::unique_ptr<Level> level(_factory.CreateLevel(std::move(layers)));

	return std::move(level);
}

FromJsonLevelLoader::FromJsonLevelLoader(ITextureManager&textureManager,LayerParsersCreator&layerParsersCreator,Factory&factory)
	:_textureManager(textureManager), _layerParsersCreator(layerParsersCreator), _factory(factory)
{
}

std::vector<std::unique_ptr<LayerBase>> FromJsonLevelLoader::ParseLayers(nlohmann::basic_json<> level_json,std::vector<Properties::Tileset>&&tilesets)
{
	_layerParsersCreator.AddTilesets(std::move(tilesets));

	vector<std::unique_ptr<LayerBase>>layers;

	for(const auto&json:level_json["layers"])
	{
		const auto &type = json["type"].get<std::string>();

		auto layerParser=_layerParsersCreator.Create(type);

		auto newLayer=layerParser->Parse(json);

		layers.emplace_back(std::move(newLayer));	
	}
	return layers;
}

std::vector<Properties::Tileset> FromJsonLevelLoader::ParseTilesets(nlohmann::basic_json<> json)
{
	std::vector<Properties::Tileset> tilesets;
	for (const auto&tileset : json["tilesets"])
	{
		Properties::Tileset newTileset;

		auto source = tileset["source"].get<string>();
		auto firstgId = tileset["firstgid"].get<int>();

		ifstream tilesetStream(source);

		auto tilesetJson = json::parse(tilesetStream);

		newTileset = tilesetJson;

		newTileset.Source = source;
		newTileset.FirstGridId = firstgId;

		_textureManager.LoadTextureFromFile(newTileset.ImageSource, newTileset.Name);

		tilesets.emplace_back(newTileset);
	}
	return std::move(tilesets);
}

