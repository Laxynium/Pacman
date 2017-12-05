#include "MainMenuState.h"
#include "SpecialSDLActionType.h"

MainMenuState::MainMenuState(std::shared_ptr<IRenderer>renderer,std::shared_ptr<IInputHandler> inputHandler,std::shared_ptr<ITextureManager>textureManager): _renderer(renderer), _inputHandler(inputHandler), _textureManager(textureManager)
{
	_stateName = "MainMenuState";

	/*_textureManager->LoadTextureFromFile("Assets/PlayButton.png", "playButton");

	_textureManager->LoadTextureFromFile("Assets/QuitButton.png", "quitButton");

	auto _startButton = std::make_shared<Button>(_renderer, _inputHandler,_textureManager);
	_startButton->Clicked+=[this]()
	{
		ChangedState("PlayState");
	};
	_startButton->SetPosition({ 298, 500 });
	_startButton->SetWidth(300);
	_startButton->SetHeight(80);
	_startButton->SetColumnsCount(3);
	_startButton->SetFramesCount(30);
	_startButton->SetTextureName("playButton");


	auto _quitButton= std::make_shared<Button>(_renderer, _inputHandler, _textureManager);
	_quitButton->Clicked += [this]()
	{
		StateEnded();
	};
	_quitButton->SetPosition({ 298, 700 });
	_quitButton->SetWidth(300);
	_quitButton->SetHeight(80);
	_quitButton->SetColumnsCount(3);
	_quitButton->SetFramesCount(30);
	_quitButton->SetTextureName("quitButton");

	_objects.insert(_objects.end(), {_startButton,_quitButton});*/

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
	std::cout << "On enter in MenuState\n";
}

void MainMenuState::OnExit()
{
	_inputHandler->RemoveBinding("EnterPressed");
	std::cout << "On exit in MenuState\n";
}
