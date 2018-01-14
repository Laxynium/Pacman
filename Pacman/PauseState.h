#pragma once
#include "IGameState.h"
#include "IInputHandler.h"
#include "IRenderer.h"
#include "MenuStateBase.h"

class PauseState:public MenuStateBase
{
	std::shared_ptr<IInputHandler> _inputHandler;
protected:
	void BindActionToButton(Button& button) override;
public:
	PauseState(std::shared_ptr<IInputHandler> inputHandler);

	void HandleInput() override;

	void Update() override;

	void Draw() override;

	void OnEnter() override;

	void OnExit() override;

};
