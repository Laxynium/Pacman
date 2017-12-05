#pragma once
#include "IGameState.h"
#include "IInputHandler.h"
#include "IRenderer.h"

class PauseState:public IGameState
{
	std::shared_ptr<IInputHandler> _inputHandler;
	std::shared_ptr<IRenderer> _renderer;
public:
	PauseState(std::shared_ptr<IRenderer>renderer,std::shared_ptr<IInputHandler> inputHandler);
	void HandleInput() override;
	void Update() override;
	void Draw() override;
	void OnEnter() override;
	void OnExit() override;

};
