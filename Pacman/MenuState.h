#pragma once
#include "IGameState.h"
#include "IInputHandler.h"
#include "Button.h"

class MenuState:public IGameState
{
	std::shared_ptr<IRenderer> _renderer;

	std::shared_ptr<IInputHandler> _inputHandler;

	std::shared_ptr<Button>_startButton;

	std::shared_ptr<Button>_quitButton;

	std::shared_ptr<ITextureManager> _textureManager;

private://methods
	void OnEnterPressed();
public:
	MenuState(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler,
	          std::shared_ptr<ITextureManager> textureManager);
	~MenuState();
	void Update() override;

	void Draw() override;

	void HandleInput() override;

	void OnEnter() override;

	void OnExit() override;

};
