#pragma once
#include <memory>
#include "BoostDI.h"
#include <memory>
#include "IRenderer.h"
#include "IGameState.h"
#include "IInputHandler.h"
#include "GameStateMachine.h"
namespace di=boost::di;
class Game
{
	std::shared_ptr<IRenderer> _renderer;

	std::shared_ptr<GameStateMachine> _gameStateMachine;

	bool _isRunning = true;
public:
	Game(std::shared_ptr<IRenderer> renderer,std::shared_ptr<GameStateMachine>gameStateMachine);

	Game(Game&& other) noexcept = default;

	~Game() = default;

	bool IsRunning() const;

	void HandleInput();

	void Update() const;
	
	void Render() const;
};

