#pragma once
#include <memory>
#include "IGameState.h"
#include "IRenderer.h"
#include "IInputHandler.h"
#include "ILevelLoader.h"
#include "GameLogicHandler.h"
#include "GameHud.h"

class GameStateFactory
{
	std::shared_ptr<IRenderer> _renderer;
	std::shared_ptr<IInputHandler> _inputHandler;
	std::shared_ptr<ILevelLoader> _levelLoader;
	std::shared_ptr<ICollisionManager> _collisionManager;
	std::shared_ptr<GameLogicHandler> _gameLogicHandler;
	std::shared_ptr<GameHud> _gameHud;
	std::map<std::string, std::function<std::shared_ptr<IGameState>()>>_mappedStates;
public:
	GameStateFactory(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler,
	                 std::shared_ptr<ILevelLoader> levelLoader, std::shared_ptr<ICollisionManager> collisionManager,
	                 std::shared_ptr<GameLogicHandler> gameLogicHandler, std::shared_ptr<GameHud> gameHud);

	std::shared_ptr<IGameState> CreateState(const std::string&name);

};
