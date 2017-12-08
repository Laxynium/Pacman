#include "MainMenuState.h"
#include "SpecialSDLActionType.h"

MainMenuState::MainMenuState(std::shared_ptr<IRenderer>renderer,std::shared_ptr<IInputHandler> inputHandler,std::shared_ptr<ITextureManager>textureManager): _renderer(renderer), _inputHandler(inputHandler), _textureManager(textureManager)
{
	_stateName = "MainMenuState";
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::OnEnterPressed()
{
	ChangedState("PlayState");
}

void MainMenuState::BindActionToButton(Button& button)
{
	std::function<void()>func;

	if (button.GetName() == "playButton")
		func = [this]() {this->ChangedState("PlayState"); };

	if (button.GetName() == "quitButton")
		func = [this]() {this->StateEnded(); };

	button.Clicked += func;
}

void MainMenuState::Update()
{
	for (auto&object : _objects)
		object->Update();
	//std::cout << "Updating in MenuState\n";
}

void MainMenuState::Draw()
{
	for (auto&object : _objects)
		object->Draw();
	//std::cout << "Drawing in MenuState\n";
}

void MainMenuState::HandleInput()
{
	//std::cout << "Handling input in MenuState\n";
	_inputHandler->HandleActions();
}

void MainMenuState::OnEnter()
{
	_inputHandler->AddBindings({ { (new SpecialSDLActionType(SDL_SCANCODE_RETURN))->SetUniuqueName("EnterPressed"),[this]()
	{
		OnEnterPressed();
	} } });
	//std::cout << "On enter in MenuState\n";
}

void MainMenuState::OnExit()
{
	_inputHandler->RemoveBinding("EnterPressed");
	//std::cout << "On exit in MenuState\n";
}
