#include "Button.h"
#include "SDLActionType.h"
#include "MouseMoveActionArg.h"
#include "Rect.h"
#include "ActionArg.h"
#include "ITextureManager.h"

int Button::_id = 0;

Button::Button(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler,std::shared_ptr<ITextureManager>textureManager) : _renderer(renderer),
_inputHandler(
	inputHandler), _textureManager(textureManager)
{
	_id++;

	_mouseMove += std::to_string(_id);

	_buttonDown += std::to_string(_id);

	_buttonUp += std::to_string(_id);

	_inputHandler->AddBindings({ { (new SDLActionType(SDL_MOUSEMOTION,0))->SetUniuqueName(_mouseMove),[&](std::shared_ptr<ActionArg>action)
	{
		auto &mouseMoveActionType = dynamic_cast<MouseMoveActionArg&>(*action);

		_currentMousePosition = { static_cast<double>(mouseMoveActionType.GetX()), static_cast<double>(mouseMoveActionType.GetY()) };

		if(IsHovered())
		{
			_isHovered = true;
		}else
		{
			_isHovered = false;
		}

	} } });

	_inputHandler->AddBindings({ { (new SDLActionType(SDL_MOUSEBUTTONDOWN,0))->SetUniuqueName(_buttonDown),[&]()
	{
		_isButtonPressed = true;
	} } });

	_inputHandler->AddBindings({ { (new SDLActionType(SDL_MOUSEBUTTONUP,0))->SetUniuqueName(_buttonUp),[&]()
	{
		this->ManageClick();

		_isButtonPressed = false;
	} } });

	_currentFrame = 0;
	_framesCount = 3;
	_columnsCount = 3;

}

void Button::ManageClick()
{
	if (!IsHovered())
		return;
	//do actions on click
	Clicked();
}

bool Button::IsHovered()
{
	auto mouseX = _currentMousePosition.X(), mouseY = _currentMousePosition.Y(), x = _position.X(), y = _position.Y();
	auto width = GetWidth(), height = GetHeight();
	if (mouseX<x || mouseX>x + width || mouseY<y || mouseY>y + height)
		return false;
	return true;
}

Button::~Button()
{
	_inputHandler->RemoveBinding(_mouseMove);

	_inputHandler->RemoveBinding(_buttonDown);

	_inputHandler->RemoveBinding(_buttonUp);
}

void Button::Draw()
{
	int x=(_currentFrame%_columnsCount)*(_width);
	int y = (_currentFrame/ _columnsCount) * _height;
	_renderer->CopyEx(_textureManager->FindTexture(_textureName), &Rect{ x,y,_width,_height }, &Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height });
}

void Button::Update()
{
	_currentFrame = 0;
	if(_isHovered)
	{
		_currentFrame = 1;
		if (_isButtonPressed)
		{
			_currentFrame = 2;
		}
	}
}