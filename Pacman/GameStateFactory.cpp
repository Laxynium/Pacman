#include "GameStateFactory.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "GameStateNames.h"

GameStateFactory::GameStateFactory(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler,std::shared_ptr<ITextureManager>textureManager,
                                   std::shared_ptr<ILevelLoader> levelLoader,
                                   std::shared_ptr<ICollisionManager> collisionManager,
                                   std::shared_ptr<GameLogicHandler> gameLogicHandler,
                                   std::shared_ptr<GameHud> gameHud): _renderer(renderer), _inputHandler(inputHandler),
                                                                      _levelLoader(levelLoader),
                                                                      _collisionManager(collisionManager),
                                                                      _gameLogicHandler(gameLogicHandler),
                                                                      _gameHud(gameHud), _textureManager(textureManager)
{
	auto createPlayState = [&]()->std::shared_ptr<IGameState> {return std::make_shared<PlayState>(_renderer, _inputHandler, _textureManager, _levelLoader,
		_collisionManager, _gameLogicHandler, _gameHud); };

	auto createPauseState = [&]()->std::shared_ptr<IGameState> {return std::make_shared<PauseState>(_inputHandler); };

	auto createMenuState = [&]()->std::shared_ptr<IGameState> {return std::make_shared<MainMenuState>(_inputHandler); };

	auto createGameOverState = [&]()->std::shared_ptr<IGameState> {return std::make_shared<GameOverState>(_inputHandler,_gameLogicHandler,_renderer); };

	_mappedStates[GameStateNames::PlayState] = createPlayState;

	_mappedStates[GameStateNames::PauseState] = createPauseState;

	_mappedStates[GameStateNames::MainMenuState] = createMenuState;

	_mappedStates[GameStateNames::GameOverState] = createGameOverState;
}

std::shared_ptr<IGameState> GameStateFactory::CreateState(const std::string& name)
{
	const auto where=_mappedStates.find(name);
	if(where!=_mappedStates.end())
		return _mappedStates[name]();
	return nullptr;
}
