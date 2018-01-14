#pragma once
#include "IGameState.h"
#include "IHandleInput.h"
#include <memory>
#include "Event.h"
#include "IInputHandler.h"
#include "GameStateFactory.h"
#include "IStatesLoader.h"

class GameStateMachine:public IUpdateable,public IDrawable,public IHandleInput
{
	std::shared_ptr<IGameState>_currentState;

	std::shared_ptr<IGameState>_temporaryState;

	std::vector<std::shared_ptr<IGameState>>_gameStates;

	std::shared_ptr<IInputHandler> _inputHandler;

	std::shared_ptr<GameStateFactory> _gameStateFactory;

	std::shared_ptr<IStatesLoader> _statesLoader;

	bool _justRemovedState = false;

	const std::string _statesFileName = "Assets/GameStates.json";

private://methods
	void OnStateEnded();
	void OnPushedState(const std::string&stateName);
	void OnChangedState(const std::string&stateName);
	void SetupStateBindings(std::shared_ptr<IGameState>& state);
public:
	GameStateMachine(std::shared_ptr<IInputHandler>inputHandler,std::shared_ptr<GameStateFactory>gameStateFactory,std::shared_ptr<IStatesLoader>statesLoader);


	Event<void>GameHasEnded;

	void HandleInput() override;

	void Update() override;

	void Draw() override;	
};
