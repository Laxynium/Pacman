#pragma once
#include "IGameState.h"
#include "IHandleInput.h"
#include <memory>
#include "Event.h"
#include "BoostDI.h"
#include "IInputHandler.h"
#include "GameStateFactory.h"

class GameStateMachine:public IUpdateable,public IDrawable,public IHandleInput
{
	std::shared_ptr<IGameState>_currentState;
	std::shared_ptr<IInputHandler> _inputHandler;
	std::vector<std::shared_ptr<IGameState>>_gameStates;
	std::shared_ptr<GameStateFactory> _gameStateFactory;

	std::shared_ptr<IGameState>_temporaryState;

	bool _justRemovedState = false;

private://methods
	void OnStateEnded();
	void OnPushedState(const std::string&stateName);
	void OnChangedState(const std::string&stateName);
public:
	GameStateMachine(std::shared_ptr<IInputHandler>inputHandler,std::shared_ptr<GameStateFactory>gameStateFactory);

	Event<void>GameHasEnded;

	void HandleInput() override;

	void Update() override;

	void Draw() override;	
};
