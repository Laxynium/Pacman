#include "GameStateFactory.h"
#include "PlayState.h"

GameStateFactory::GameStateFactory(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler,
                                   std::shared_ptr<ILevelLoader> levelLoader,
                                   std::shared_ptr<ICollisionManager> collisionManager,
                                   std::shared_ptr<GameLogicHandler> gameLogicHandler,
                                   std::shared_ptr<GameHud> gameHud): _renderer(renderer), _inputHandler(inputHandler),
                                                                      _levelLoader(levelLoader),
                                                                      _collisionManager(collisionManager),
                                                                      _gameLogicHandler(gameLogicHandler),
                                                                      _gameHud(gameHud)
{
	auto createPlayState = [&]()->std::shared_ptr<IGameState> {return std::make_shared<PlayState>(_renderer, _inputHandler, _levelLoader,
		_collisionManager, _gameLogicHandler, _gameHud); };

	_mappedStates["PlayState"] = createPlayState;
}

std::shared_ptr<IGameState> GameStateFactory::CreateState(const std::string& name)
{
	auto where=_mappedStates.find(name);
	if(where!=_mappedStates.end())
		return _mappedStates[name]();
	return nullptr;
}
