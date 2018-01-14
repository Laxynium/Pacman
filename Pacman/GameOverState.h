#pragma once
#include "MenuStateBase.h"

class GameOverState:public MenuStateBase
{

	std::shared_ptr<IInputHandler> _inputHandler;
public:
	GameOverState(const std::shared_ptr<IInputHandler>& input_handler);

	void Draw() override;

	void Update() override;

	void HandleInput() override;

	void OnEnter() override;

	void OnExit() override;

protected:
	void BindActionToButton(Button& button) override;
};
