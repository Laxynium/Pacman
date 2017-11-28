#pragma once
#include <memory>
#include "BoostDI.h"
#include "IInputHandler.h"
#include <memory>
#include "IRenderer.h"

#include "ILevelLoader.h"
#include "Ball.h"
#include "Ghost.h"
#include "BoostDI.h"
#include "GameLogicHandler.h"
#include "BoostDI.h"
#include "GameHud.h"
#include "Pacman.h"
namespace di=boost::di;
class Game
{
	std::unique_ptr<IInputHandler> _input_handler;

	std::shared_ptr<IRenderer> _renderer;

	bool _isRunning = true;

	std::unique_ptr<Pacman> _pacman;

	std::vector<std::unique_ptr<Ghost>> _ghosts;

	std::shared_ptr<ILevelLoader> _levelLoader;

	std::shared_ptr<ICollisionManager> _collisionManager;

	std::vector<std::unique_ptr<GameObject>>_balls;

	std::unique_ptr<Level> _level;

	std::shared_ptr<GameLogicHandler> _gameLogicHandler;

	std::shared_ptr<GameHud> _gameHud;

	void OnGameEnd();


public:
	Game(std::shared_ptr<IRenderer> renderer ,std::unique_ptr<IInputHandler> inputHandler,std::shared_ptr<ILevelLoader>levelLoader,
	     std::shared_ptr<ICollisionManager>collisionManager, std::shared_ptr<GameLogicHandler>gameLogicHandler, std::shared_ptr<GameHud>gameHud);
	void OnLevelEnd();


	Game(Game&& other) noexcept = default;

	~Game() = default;

	bool IsRunning() const;

	void HandleInput();

	void Update() const;
	
	void Render() const;
private:
	void BindInput();
};

