#include "LayerParsersCreator.h"
#include "TileLayerParser.h"
#include "ObjectLayerParser.h"

LayerParsersCreator::LayerParsersCreator(ITextureManager&textureManager,IRenderer&renderer,ICollisionManager&collisionManager, GameLogicHandler&gameLogicHandler,
	Factory &factory,IInnerObjectLayerParsersCreator &innerObjectLayerParsersCreator):
		_textureManager(textureManager), _renderer(renderer), _collisionManager(collisionManager), _gameLogicHandler(gameLogicHandler), 
			_factory(factory), _innerObjectLayerParsersCreator(innerObjectLayerParsersCreator)
{
	_mappedParsers["objectgroup"]= [&]() {return std::make_unique<ObjectLayerParser>(_collisionManager,_gameLogicHandler,factory, _innerObjectLayerParsersCreator); };
}

void LayerParsersCreator::AddTilesets(std::vector<Properties::Tileset>&& tilesets)
{
	_tilesets = std::make_unique<std::vector<Properties::Tileset>>(std::move(tilesets));
	_mappedParsers["tilelayer"] = [&]() {return std::make_unique<TileLayerParser>(_collisionManager, *_tilesets,_factory); };
}

std::unique_ptr<ILayerParser> LayerParsersCreator::Create(const std::string& type)
{ 
	//TODO propably here is bug
	if (_tilesets==nullptr)
		throw std::exception("Tilesets were not set.");

	return _mappedParsers[type]();
}
