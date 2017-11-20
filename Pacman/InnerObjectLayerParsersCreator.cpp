#include "InnerObjectLayerParsersCreator.h"

InnerObjectLayerParsersCreator::InnerObjectLayerParsersCreator(Factory& factory, ICollisionManager& collisionManager,GameLogicHandler&gameLogicHandler):
	_collisionManager(collisionManager), _factory(factory), _gameLogicHandler(gameLogicHandler)
{
	_parsers["Balls"] = [&]() { return std::make_unique<BallObjectLayerParser>(_factory, _collisionManager,_gameLogicHandler); };
	_parsers["Ghosts"] = [&]() { return std::make_unique<EnemiesObjectLayerParser>(_factory, _collisionManager, _gameLogicHandler); };
}

std::unique_ptr<IInnerObjectLayerParser> InnerObjectLayerParsersCreator::Create(const std::string& type)
{
	return _parsers[type]();
}

