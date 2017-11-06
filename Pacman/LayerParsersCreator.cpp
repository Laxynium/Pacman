#include "LayerParsersCreator.h"
#include "TileLayerParser.h"

LayerParsersCreator::LayerParsersCreator(ITextureManager&textureManager,IRenderer&renderer,ICollisionManager&collisionManager): 
		_textureManager(textureManager), _renderer(renderer), _collisionManager(collisionManager)
{
}

void LayerParsersCreator::AddTilesets(std::vector<Test::Tileset>&& tilesets)
{
	_tilesets = std::make_unique<std::vector<Test::Tileset>>(std::move(tilesets));
}

std::unique_ptr<ILayerParser> LayerParsersCreator::Create(const std::string& type)
{ 
	//TODO propably here is bug
	if (_tilesets==nullptr)
		throw std::exception("Tilesets were not set.");

	if(_mappedParsers.find("tilelayer")==std::end(_mappedParsers))
		_mappedParsers["tilelayer"] = [&]() {return std::make_unique<TileLayerParser>(_textureManager, _renderer, _collisionManager,*_tilesets); };

	return _mappedParsers[type]();
}
