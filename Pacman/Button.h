#pragma once
#include "GameObject.h"
#include "IRenderer.h"
#include "IInputHandler.h"
#include "Event.h"
#include "BoostDI.h"
#include "ITextureManager.h"
#include <ctime>

class Button :public GameObject
{
	std::shared_ptr<IRenderer> _renderer;
	std::shared_ptr<IInputHandler> _inputHandler;
	std::shared_ptr<ITextureManager> _textureManager;

	Vector2D _currentMousePosition;

	bool _isButtonPressed;

	void ManageClick();

	bool IsHovered();

	bool _isHovered = false;

	bool _animPlayed = false;
public:
	Button(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler, std::shared_ptr<ITextureManager>textureManager);

	virtual ~Button();

	void Draw() override;

	void Update() override;

	Event<void> Clicked;
};
