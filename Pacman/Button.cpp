#include "Button.h"
#include "SDLActionType.h"
#include "MouseMoveActionArg.h"
#include "Rect.h"
#include "ActionArg.h"
#include "ITextureManager.h"

Button::Button(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler,std::shared_ptr<ITextureManager>textureManager) : _renderer(renderer),
_inputHandler(
	inputHandler), _textureManager(textureManager)
{
	_inputHandler->AddBindings({ { (new SDLActionType(SDL_MOUSEMOTION,0))->SetUniuqueName("MouseMove"),[&](std::shared_ptr<ActionArg>action)
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
	if (!IsHovered())return;
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
	_inputHandler->RemoveBinding("MouseMove");

	_inputHandler->RemoveBinding("ButtonDown");

	_inputHandler->RemoveBinding("ButtonUp");
}

void Button::Draw()
{
	int x=(_currentFrame%_columnsCount)*(_width);
	int y = (_currentFrame/ _columnsCount) * _height;
	_renderer->CopyEx(_textureManager->FindTexture(_textureName), &Rect{ x,y,_width,_height }, &Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height });
}

void Button::Update()
{
	if(_isHovered)
	{
		clock_t currentTime = clock();

		if (currentTime - _startTime < 20)
			return;

		_startTime = currentTime;

		if (!_animPlayed)
			(++_currentFrame%=_framesCount);
		/*if(_currentFrame>=30)
		{
			_animPlayed = true;
			_currentFrame = 0;
		}*/
	}else
	{
		_animPlayed = false;
		_currentFrame = 0;
	}
}