#include "MenuState.h"
#include "SpecialSDLActionType.h"
#include "IRenderer.h"
#include "Rect.h"

MenuState::MenuState(std::shared_ptr<IRenderer>renderer,std::shared_ptr<IInputHandler>inputHandler): _renderer(renderer),_inputHandler(inputHandler)
{
	_stateName = "MenuState";
	_startButton = std::make_shared<Button>(_renderer, _inputHandler);
	_startButton->SetPosition({ 100,100 });
	_startButton->SetHeight(100);
	_startButton->SetWidth(400);
	_startButton->Clicked+=[this]()
	{
		ChangedState("PlayState");
		std::cout << "U has clicked me\n";
	};
}

void MenuState::HandleInput()
{
	//std::cout << "Handling input in MenuState\n";
	_inputHandler->HandleActions();
}


void MenuState::Update()
{
	_startButton->Update();
	//std::cout << "Updating in MenuState\n";
}

void MenuState::Draw()
{
	//_renderer->FillRect(Rect{ 0,0,200,200,Color{150,150,150} });
	_startButton->Draw();
	//std::cout << "Drawing in MenuState\n";
}


void MenuState::OnEnter()
{
	_inputHandler->AddBindings({ { (new SpecialSDLActionType(SDL_SCANCODE_RETURN))->SetUniuqueName("EnterPressed"),[this]()
	{
		ChangedState("PlayState");
	} } });
	std::cout << "On enter in MenuState\n";
}

void MenuState::OnExit()
{
	_inputHandler->RemoveBinding("EnterPressed");
	std::cout << "On exit in MenuState\n";
}
