#pragma once
#include "IGameState.h"
#include "IInputHandler.h"

class PauseState:public IGameState
{
public:
	PauseState(std::shared_ptr<IInputHandler> inputHandler);
	void HandleInput() override;
	void Update() override;
	void Draw() override;
	void OnEnter() override;
	void OnExit() override;
	std::shared_ptr<IInputHandler> _inputHandler;
};
