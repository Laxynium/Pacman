#include "PauseState.h"
#include "SpecialSDLActionType.h"
#include "IRenderer.h"

PauseState::PauseState(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler): _inputHandler(inputHandler), _renderer(renderer)
{
	_stateName = "PauseState";
}

void PauseState::HandleInput()
{
	_inputHandler->HandleActions();
}

void PauseState::Update()
{
}

void PauseState::Draw()
{
}

void PauseState::OnEnter()
{
	_inputHandler->AddBindings({ {(new SpecialSDLActionType(SDL_SCANCODE_BACKSPACE))->SetUniuqueName("F1Pressed"),[this]()
	{
		ChangedState("MenuState");
	}} });
	_inputHandler->AddBindings({ { (new SpecialSDLActionType(SDL_SCANCODE_RETURN))->SetUniuqueName("EnterPressed"),[this]()
	{
		StateEnded();
	} } });
}

void PauseState::OnExit()
{
	_inputHandler->RemoveBinding("F1Pressed");
	_inputHandler->RemoveBinding("EnterPressed");
}
