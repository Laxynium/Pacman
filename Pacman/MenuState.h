#pragma once
#include "IGameState.h"
#include "IInputHandler.h"
#include "BoostDI.h"
#include "IRenderer.h"
#include "Button.h"

class MenuState:public IGameState
{
	std::shared_ptr<IInputHandler> _inputHandler;
	std::shared_ptr<IRenderer> _renderer;
	std::shared_ptr<Button> _startButton;
public:
	MenuState(std::shared_ptr<IRenderer>renderer,std::shared_ptr<IInputHandler> inputHandler);

	void HandleInput() override;

	void Update() override;

	void Draw() override;

	void OnEnter() override;

	void OnExit() override;

};
