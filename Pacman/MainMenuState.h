#pragma once
#include "IGameState.h"
#include "IInputHandler.h"
#include "Button.h"
#include "MenuStateBase.h"

class MainMenuState:public MenuStateBase
{
	std::shared_ptr<IRenderer> _renderer;

	std::shared_ptr<IInputHandler> _inputHandler;

	std::shared_ptr<ITextureManager> _textureManager;

private://methods
	void OnEnterPressed();
public:
	MainMenuState(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler,
	          std::shared_ptr<ITextureManager> textureManager);
	~MainMenuState();
	void Update() override;

	void Draw() override;

	void HandleInput() override;

	void OnEnter() override;

	void OnExit() override;

};
