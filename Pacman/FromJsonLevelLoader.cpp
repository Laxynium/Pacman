#include "FromJsonLevelLoader.h"
#include "JsonParser.h"
#include "Tileset.h"
#include "Layer.h"
#include <fstream>
#include "LayerProperties.h"

using nlohmann::json;

namespace Test {
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
	void from_json(const json& layerJson, LayerProperties& p) {
		auto data= layerJson.at("data").get<std::vector<int>>();
		p.Height = layerJson.at("height").get<int>();
		p.Width = layerJson.at("width").get<int>();
		p.X = layerJson.at("x").get<int>();
		p.Y = layerJson.at("y").get<int>();
		p.Name = layerJson.at("name").get<std::string>();
		p.SetData(data);
		p.IsCollidable = layerJson.at("collidable").get<bool>();	
	}
}

std::unique_ptr<Level> FromJsonLevelLoader::LoadLevel(const std::string& fileName)
{
	ifstream jsonFileStream(fileName);

	if(!jsonFileStream.good())
	{	
		throw std::exception("Couldn't open file.");
	}

	const auto levelJson=json::parse(jsonFileStream);

	auto layers = ParseLayers(levelJson);

	auto tilesets = ParseTilesets(levelJson);
	
	//TODO here is something wrong with that tilesets
	for (auto&layer : layers)
		layer.Properties().SetTilesets(tilesets);

	std::for_each(layers.begin(), layers.end(), [](auto&layer) {layer.GenerateTiles(); });

	return make_unique<Level>(_renderer, layers, tilesets,_textureManager);
}

FromJsonLevelLoader::FromJsonLevelLoader(IRenderer&renderer,ITextureManager&textureManager,ICollisionManager&collisionManager)
	:_renderer(renderer),_textureManager(textureManager), _collisionManager(collisionManager)
{
}


FromJsonLevelLoader::~FromJsonLevelLoader()
{
}


std::vector<Test::Layer> FromJsonLevelLoader::ParseLayers(nlohmann::basic_json<> level_json)
{
	vector<Test::Layer>layers;
	for(const auto&json:level_json["layers"])
	{
		Test::Layer layer(_textureManager,_renderer);

		const Test::LayerProperties layerProp = json;
		
		layer.SetProperties(layerProp);

		layers.emplace_back(layer);	
	}
	return layers;
}

std::vector<Test::Tileset> FromJsonLevelLoader::ParseTilesets(nlohmann::basic_json<> json)
{
	std::vector<Test::Tileset> tilesets;
	for (const auto&tileset : json["tilesets"])
	{
		Test::Tileset newTileset;

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
	return tilesets;
}

