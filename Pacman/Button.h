#pragma once
#include "GameObject.h"
#include "IRenderer.h"
#include "IInputHandler.h"
#include "Event.h"

class Button :public GameObject
{
	std::shared_ptr<IRenderer> _renderer;
	std::shared_ptr<IInputHandler> _inputHandler;

	Vector2D _currentMousePosition;
	bool _isButtonPressed;

	void ManageClick();

public:
	Button(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler);

	virtual ~Button();

	void Draw() override;

	void Update() override;

	Event<void> Clicked;

};