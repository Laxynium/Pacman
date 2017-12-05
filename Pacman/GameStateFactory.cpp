﻿#include "GameStateFactory.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MenuState.h"

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
	auto createPlayState = [&]()->std::shared_ptr<IGameState> {return std::make_shared<PlayState>(_renderer, _inputHandler, _levelLoader,
		_collisionManager, _gameLogicHandler, _gameHud); };

	auto createPauseState = [&]()->std::shared_ptr<IGameState> {return std::make_shared<PauseState>(_renderer,_inputHandler); };

	auto createMenuState = [&]()->std::shared_ptr<IGameState> {return std::make_shared<MenuState>(_renderer,_inputHandler,_textureManager); };

	_mappedStates["PlayState"] = createPlayState;

	_mappedStates["PauseState"] = createPauseState;

	_mappedStates["MenuState"] = createMenuState;
}

std::shared_ptr<IGameState> GameStateFactory::CreateState(const std::string& name)
{
	const auto where=_mappedStates.find(name);
	if(where!=_mappedStates.end())
		return _mappedStates[name]();
	return nullptr;
}
