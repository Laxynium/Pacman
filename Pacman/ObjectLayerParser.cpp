#include "ObjectLayerParser.h"
#include "ObjectLayer.h"


ObjectLayerParser::ObjectLayerParser(ICollisionManager& collisionManager, 
										GameLogicHandler &gameLogicHandler, Factory&factory, IInnerObjectLayerParsersCreator&objectLayerParsersCreator):
											_collisionManager(collisionManager), _gameLogicHandler(gameLogicHandler), _factory(factory), _objectLayerParsersCreator(objectLayerParsersCreator)
{
}

std::unique_ptr<LayerBase> ObjectLayerParser::Parse(nlohmann::basic_json<> json)
{
	auto objectLayerParser = _objectLayerParsersCreator.Create(json["name"].get<std::string>());

	auto objectLayer=objectLayerParser->Parse(json);

	return objectLayer;
}
