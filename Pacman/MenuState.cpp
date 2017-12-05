#include "MenuState.h"
#include "SpecialSDLActionType.h"

MenuState::MenuState(std::shared_ptr<IRenderer>renderer,std::shared_ptr<IInputHandler> inputHandler,std::shared_ptr<ITextureManager>textureManager): _renderer(renderer), _inputHandler(inputHandler), _textureManager(textureManager)
{
	_stateName = "MenuState";

	_textureManager->LoadTextureFromFile("Assets/PlayButton.png", "playButton");

	_startButton = std::make_shared<Button>(_renderer, _inputHandler,_textureManager);
	_startButton->Clicked+=[this]()
	{
		ChangedState("PlayState");
	};
	_startButton->SetPosition({ 298, 300 });
	_startButton->SetWidth(300);
	_startButton->SetHeight(100);

	_quitButton= std::make_shared<Button>(_renderer, _inputHandler, _textureManager);
	_quitButton->Clicked += [this]()
	{
		StateEnded();
	};
	_quitButton->SetPosition({ 298, 500 });
	_quitButton->SetWidth(300);
	_quitButton->SetHeight(100);
}

MenuState::~MenuState()
{
}

void MenuState::OnEnterPressed()
{
	ChangedState("PlayState");
}
void MenuState::Update()
{
	_startButton->Update();
	_quitButton->Update();
	//std::cout << "Updating in MenuState\n";
}

void MenuState::Draw()
{
	_startButton->Draw();
	_quitButton->Draw();
	//std::cout << "Drawing in MenuState\n";
}

void MenuState::HandleInput()
{
	//std::cout << "Handling input in MenuState\n";
	_inputHandler->HandleActions();
}

void MenuState::OnEnter()
{
	_inputHandler->AddBindings({ { (new SpecialSDLActionType(SDL_SCANCODE_RETURN))->SetUniuqueName("EnterPressed"),[this]()
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
