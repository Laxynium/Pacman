#include "InnerObjectLayerParsersCreator.h"

InnerObjectLayerParsersCreator::InnerObjectLayerParsersCreator(Factory& factory, ICollisionManager& collisionManager,
	GameLogicHandler&gameLogicHandler,ITextureManager&textureManager):
	_collisionManager(collisionManager), _factory(factory), _gameLogicHandler(gameLogicHandler), _textureManager(textureManager)
{
	_parsers["Balls"] = [&]() { return std::make_unique<BallObjectLayerParser>(_factory, _collisionManager,_gameLogicHandler); };
	_parsers["Ghosts"] = [&]() { return std::make_unique<EnemiesObjectLayerParser>(_factory, _collisionManager, _gameLogicHandler,_textureManager); };
}

std::unique_ptr<IInnerObjectLayerParser> InnerObjectLayerParsersCreator::Create(const std::string& type)
{
	return _parsers[type]();
}

