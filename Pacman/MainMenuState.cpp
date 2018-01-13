#include "MainMenuState.h"
#include "SpecialSDLActionType.h"
#include "GameStateNames.h"

MainMenuState::
MainMenuState(std::shared_ptr<IRenderer> renderer, std::shared_ptr<IInputHandler> inputHandler): _renderer(renderer),
                                                                                                 _inputHandler(
	                                                                                                 inputHandler)
{
	_stateName = GameStateNames::MainMenuState;
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::OnEnterPressed()
{
	ChangedState(GameStateNames::PlayState);
}

void MainMenuState::BindActionToButton(Button& button)
{
	std::function<void()>func;

	//TODO use map not ifs
	if (button.GetName() == "playButton")
		func = [this]() {this->ChangedState(GameStateNames::PlayState); };

	if (button.GetName() == "quitButton")
		func = [this]() {this->StateEnded(); };

	button.Clicked += func;
}

void MainMenuState::Update()
{
	for (auto&object : _objects)
		object->Update();
}

void MainMenuState::Draw()
{
	for (auto&object : _objects)
		object->Draw();
}

void MainMenuState::HandleInput()
{
	_inputHandler->HandleActions();
}

void MainMenuState::OnEnter()
{
	_inputHandler->AddBindings({ { (new SpecialSDLActionType(SDL_SCANCODE_RETURN))->SetUniuqueName("EnterPressed"),[this]()
	{
		OnEnterPressed();
	} } });
}

void MainMenuState::OnExit()
{
	_inputHandler->RemoveBinding("EnterPressed");
}
