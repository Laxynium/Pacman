#include "Button.h"
#include "SDLActionType.h"
#include "MouseMoveActionArg.h"
#include "Rect.h"
#include "ActionArg.h"

Button::Button(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler) : _renderer(renderer),
_inputHandler(
	inputHandler)
{
	_inputHandler->AddBindings({ { (new SDLActionType(SDL_MOUSEMOTION,0))->SetUniuqueName("MouseMove"),[&](std::shared_ptr<ActionArg>action)
	{
		auto &mouseMoveActionType = dynamic_cast<MouseMoveActionArg&>(*action);

		_currentMousePosition = { static_cast<double>(mouseMoveActionType.GetX()), static_cast<double>(mouseMoveActionType.GetY()) };

	} } });

	_inputHandler->AddBindings({ { (new SDLActionType(SDL_MOUSEBUTTONDOWN,0))->SetUniuqueName("ButtonDown"),[&]()
	{
		_isButtonPressed = true;
	} } });

	_inputHandler->AddBindings({ { (new SDLActionType(SDL_MOUSEBUTTONUP,0))->SetUniuqueName("ButtonUp"),[&]()
	{
		this->ManageClick();

		_isButtonPressed = false;
	} } });

}

void Button::ManageClick()
{
	auto mouseX = _currentMousePosition.X(), mouseY = _currentMousePosition.Y(), x = _position.X(), y = _position.Y();
	auto width = GetWidth(), height = GetHeight();
	if (mouseX<x || mouseX>x + width || mouseY<y || mouseY>y + height)
		return;
	//do actions on click
	Clicked();
}

Button::~Button()
{
	_inputHandler->RemoveBinding("MouseMove");

	_inputHandler->RemoveBinding("ButtonDown");

	_inputHandler->RemoveBinding("ButtonUp");
}

void Button::Draw()
{
	_renderer->FillRect(Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height,Color{ 150,150,150 } });
}

void Button::Update()
{

}