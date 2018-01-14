#pragma once
#include "MenuStateBase.h"
#include "Text.h"

class OptionsState:public MenuStateBase
{
	const std::shared_ptr<IInputHandler>& _inputHandler;
	std::shared_ptr<Text>_upText;
	std::shared_ptr<Text>_leftText;
	std::shared_ptr<Text>_downText;
	std::shared_ptr<Text>_rightText;

	bool _buttonPressed=false;
	std::string _pressedButton = "";

	const std::shared_ptr<IRenderer>& _renderer;
public:
	OptionsState(const std::shared_ptr<IInputHandler>& render,const std::shared_ptr<IRenderer>&renderer);

	void OnEnter() override;

	void HandleInput() override;

	void Update() override;

	void Draw() override;
	
	void OnExit() override;

protected:
	void BindActionToButton(Button& button) override;
	
};
