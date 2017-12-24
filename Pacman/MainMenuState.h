#pragma once
#include "IGameState.h"
#include "IInputHandler.h"
#include "Button.h"
#include "MenuStateBase.h"

class MainMenuState:public MenuStateBase
{
	std::shared_ptr<IRenderer> _renderer;

	std::shared_ptr<IInputHandler> _inputHandler;
private://methods
	void OnEnterPressed();
protected:
	void BindActionToButton(Button& button) override;
public:
	MainMenuState(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler);
	~MainMenuState();
	void Update() override;

	void Draw() override;

	void HandleInput() override;

	void OnEnter() override;

	void OnExit() override;

};
