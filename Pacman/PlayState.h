#pragma once
#include "IGameState.h"
#include "GameHud.h"
#include "GameLogicHandler.h"
#include "ILevelLoader.h"
#include "IInputHandler.h"
#include "Pacman.h"

class PlayState:public IGameState
{
	std::shared_ptr<IRenderer> _renderer;
	std::shared_ptr<IInputHandler> _inputHandler;
	std::shared_ptr<ILevelLoader> _levelLoader;
	std::shared_ptr<ICollisionManager> _collisionManager;
	std::shared_ptr<GameLogicHandler> _gameLogicHandler;

	std::shared_ptr<GameHud> _gameHud;

	std::unique_ptr<Pacman> _pacman;

	std::unique_ptr<Level> _level;

	const std::string _mapPath = "Assets/PacmanTiled.json";

	bool _isRunning = true;
	std::shared_ptr<ITextureManager> _textureManager;

private://methods
	void SetupPacman();

	void BindInput();

	void BindToGameLogicHandler();

	void OnLevelEnd();

	void OnGameEnd();

public:
	PlayState(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler, std::shared_ptr<ITextureManager>textureManager,
	            std::shared_ptr<ILevelLoader> levelLoader, std::shared_ptr<ICollisionManager> collisionManager,
	            std::shared_ptr<GameLogicHandler> gameLogicHandler, std::shared_ptr<GameHud> gameHud);

	~PlayState();

	void OnEnter()override;

	void HandleInput() override;

	void Update() override;

	void Draw() override;

	void OnExit() override;
	
};
