#include "MenuState.h"
#include "SpecialSDLActionType.h"

MenuState::MenuState(std::shared_ptr<IInputHandler> inputHandler): _inputHandler(inputHandler)
{
	_stateName = "MenuState";
}

MenuState::~MenuState()
{
}

void MenuState::OnEnterPressed()
{
	std::cout << "Pressed enter\n";
	PushedState("PlayState");
}
void MenuState::Update()
{
	//std::cout << "Updating in MenuState\n";
}

void MenuState::Draw()
{
	//std::cout << "Drawing in MenuState\n";
}

void MenuState::HandleInput()
{
	//std::cout << "Handling input in MenuState\n";
	_inputHandler->HandleActions();
}

void MenuState::OnEnter()
{
	_inputHandler->AddBindings({ { (new SpecialSDLActionType(SDL_SCANCODE_F1))->SetUniuqueName("EnterPressed"),[this]()
	{
		OnEnterPressed();
	} } });
	std::cout << "On enter in MenuState\n";
}

void MenuState::OnExit()
{
	_inputHandler->RemoveBinding("EnterPressed");
	std::cout << "On exit in MenuState\n";
}
