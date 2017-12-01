#include "PauseState.h"
#include "SpecialSDLActionType.h"

PauseState::PauseState(std::shared_ptr<IInputHandler> inputHandler): _inputHandler(inputHandler)
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
	_inputHandler->AddBindings({{(new SpecialSDLActionType(SDL_SCANCODE_RETURN))->SetUniuqueName("EnterPressed"),[this]()
	{
		StateEnded();
	}} ,{(new SpecialSDLActionType(SDL_SCANCODE_F1))->SetUniuqueName("ESCPressed"),[this]()
	{
		ChangedState("MenuState");
	}}});
}

void PauseState::OnExit()
{
	_inputHandler->RemoveBinding("EnterPressed");
	_inputHandler->RemoveBinding("ESCPressed");
}
