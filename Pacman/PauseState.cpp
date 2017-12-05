#include "PauseState.h"
#include "SpecialSDLActionType.h"

PauseState::PauseState(std::shared_ptr<IRenderer>renderer, std::shared_ptr<IInputHandler> inputHandler) : _inputHandler(inputHandler), _renderer(renderer)
{
	_stateName = "PauseState";
}

void PauseState::BindActionToButton(Button& button)
{
	std::function<void()>func;

	if (button.GetName() == "resumeButton")
		func = [this]() {this->StateEnded(); };

	if (button.GetName() == "menuButton")
		func = [this]() {this->ChangedState("MainMenuState"); };

	button.Clicked += func;
}

void PauseState::HandleInput()
{
	_inputHandler->HandleActions();
}

void PauseState::Update()
{
	for (auto&object : _objects)
		object->Update();
}

void PauseState::Draw()
{
	for (auto&object : _objects)
		object->Draw();
}

void PauseState::OnEnter()
{
	_inputHandler->AddBindings({ { (new SpecialSDLActionType(SDL_SCANCODE_BACKSPACE))->SetUniuqueName("F1Pressed"),[this]()
	{
		ChangedState("MainMenuState");
	} } });
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
