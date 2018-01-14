#include "OptionsState.h"
#include "SDLActiveButtonsActionType.h"
#include "ActiveKeysActionArg.h"
#include "GameStateNames.h"
#include "GameSettings.h"

OptionsState::OptionsState(const std::shared_ptr<IInputHandler>& inputHandler,const std::shared_ptr<IRenderer>&renderer) :_inputHandler(inputHandler), 
	_renderer(renderer)
{
	_upText = std::make_shared<Text>(_renderer, "Key: "+GameSettings::ButtonToMoveUp, 40);
	_upText->SetPosition({ 400,320 });

	_leftText = std::make_shared<Text>(_renderer, "Key: "+ GameSettings::ButtonToMoveLeft, 40);
	_leftText->SetPosition({ 400,420 });

	_downText = std::make_shared<Text>(_renderer, "Key: "+ GameSettings::ButtonToMoveDown, 40);
	_downText->SetPosition({ 400,520 });

	_rightText = std::make_shared<Text>(_renderer, "Key: "+ GameSettings::ButtonToMoveRight, 40);
	_rightText->SetPosition({ 400,620 });

	_stateName = GameStateNames::OptionsState;
}


void OptionsState::Draw()
{
	for (auto&object : _objects)
		object->Draw();
	_upText->Draw();
	_leftText->Draw();
	_downText->Draw();
	_rightText->Draw();
}

void OptionsState::Update()
{
	for (auto&object : _objects)
		object->Update();

	_upText->Update();
	_leftText->Update();
	_downText->Update();
	_rightText->Update();

}

void OptionsState::HandleInput()
{
	_inputHandler->HandleActions();
}


void OptionsState::OnEnter()
{
	_inputHandler->AddBindings({ { (new SDLActiveButtonsActionType())->SetUniuqueName("ActiveButtons"),[&](std::shared_ptr<ActionArg>action)
	{
		auto &activeKeysActionArg = dynamic_cast<ActiveKeysActionArg&>(*action);

		auto activeKeys = activeKeysActionArg.ActiveKeys();


		for (auto key : activeKeys)
		{
			if (!_buttonPressed)
				return;

			if(_pressedButton=="upButton")
			{
				_upText->SetText("Key: " + key);
				_buttonPressed = false;
				GameSettings::ButtonToMoveUp = key;
			}

			if (_pressedButton == "leftButton")
			{
				_leftText->SetText("Key: " + key);
				_buttonPressed = false;
				GameSettings::ButtonToMoveLeft = key;

			}

			if (_pressedButton == "downButton")
			{
				_downText->SetText("Key: " + key);
				_buttonPressed = false;
				GameSettings::ButtonToMoveDown = key;

			}

			if (_pressedButton == "rightButton")
			{
				_rightText->SetText("Key: " + key);
				_buttonPressed = false;
				GameSettings::ButtonToMoveRight = key;

			}

		}		
	}}});
}

void OptionsState::OnExit()
{
	_inputHandler->RemoveBinding("ActiveButtons");
}

void OptionsState::BindActionToButton(Button& button)
{
	std::function<void()>func;

	std::string captionAfterPressed = "Press new key";
	////TODO use map not ifs
	const auto buttonName = button.GetName();
	if(buttonName=="upButton")
	{
		func = [captionAfterPressed, buttonName, this]()
		{
			if (_buttonPressed)return;
			_upText->SetText(captionAfterPressed);
			_buttonPressed = true;
			_pressedButton = buttonName;
		};
	}
	if (buttonName == "leftButton")
	{
		func = [captionAfterPressed, buttonName, this]()
		{
			if (_buttonPressed)return;
			_leftText->SetText(captionAfterPressed);
			_buttonPressed = true;
			_pressedButton = buttonName;
		};
	}
	if (buttonName == "downButton")
	{
		func = [captionAfterPressed, buttonName, this]()
		{
			if (_buttonPressed)return;
			_downText->SetText(captionAfterPressed);
			_buttonPressed = true;
			_pressedButton = buttonName;
		};
	}
	if (buttonName == "rightButton")
	{
		func = [captionAfterPressed, buttonName, this]()
		{
			if (_buttonPressed)return;
			_rightText->SetText(captionAfterPressed);
			_buttonPressed = true;
			_pressedButton = buttonName;
		};
	}

	if (buttonName == "menuButton")
		func = [this]() {StateEnded(); };

	button.Clicked += func;
}
