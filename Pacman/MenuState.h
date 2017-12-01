#pragma once
#include "IGameState.h"
#include "IInputHandler.h"

class MenuState:public IGameState
{
	std::shared_ptr<IInputHandler> _inputHandler;
private://methods
	void OnEnterPressed();
public:
	MenuState(std::shared_ptr<IInputHandler> inputHandler);
	~MenuState();
	void Update() override;

	void Draw() override;

	void HandleInput() override;

	void OnEnter() override;

	void OnExit() override;

};
