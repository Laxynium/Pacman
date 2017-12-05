#include "FromJsonStatesLoader.h"
#include <fstream>
#include "JsonParser.h"
#include "Button.h"
#include "MenuStateBase.h"
using nlohmann::json;

namespace Properties
{
	struct GameObjectProp
	{
		std::string Type;
		std::string Name;
		std::string TextureName;
		int X;
		int Y;
		int Width;
		int Height;
		int FramesCount;
		int Rows;
		int Columns;
	};
	void from_json(const json& gameObject,GameObjectProp&prop) 
	{
		prop.Type = gameObject.at("type").get<std::string>();
		prop.Name = gameObject.at("name").get<std::string>();
		prop.TextureName = gameObject.at("textureName").get<std::string>();
		prop.X = gameObject.at("x").get<int>();
		prop.Y = gameObject.at("y").get<int>();
		prop.Width = gameObject.at("width").get<int>();
		prop.Height = gameObject.at("height").get<int>();

		prop.FramesCount = gameObject.at("framesCount").get<int>();
		prop.Rows = gameObject.at("rows").get<int>();
		prop.Columns = gameObject.at("columns").get<int>();
	}
}


FromJsonStatesLoader::FromJsonStatesLoader(std::shared_ptr<IRenderer>renderer, std::shared_ptr<IInputHandler>inputHandler, std::shared_ptr<ITextureManager> textureManager) : _textureManager(
	textureManager), _inputHandler(inputHandler), _renderer(renderer)
{
}


void FromJsonStatesLoader::Load(const std::string& fileName,std::shared_ptr<IGameState>state)
{
	std::ifstream jsonFileStream(fileName);

	if(!jsonFileStream.good())
	{
		throw std::exception("Couldn't open file");
	}

	const auto statesJson = json::parse(jsonFileStream);

	auto menuStatesJson = statesJson["gameStates"]["menuStates"];

	for(auto&stateJson:menuStatesJson)
	{
		if(stateJson["name"]==state->GetStateName())
		{		
			//TODO create parsers for each state

			auto *menuState = dynamic_cast<MenuStateBase*>(state.get());

			//Right now support only menus
			if(nullptr !=menuState)
			{
				ParseAndLoadTextures(stateJson["textures"]);
				const auto gameObjects = ParseGameObjects(stateJson["gameObjects"]);
				menuState->SetObjects(gameObjects);
			}

		}
	}


}

void FromJsonStatesLoader::ParseAndLoadTextures(nlohmann::basic_json<>json)
{
	for(auto&texture:json)
	{
		const auto name = texture["name"].get<std::string>();
		const auto path = texture["path"].get<std::string>();
		_textureManager->LoadTextureFromFile(path, name);
	}	
}

std::shared_ptr<GameObject>FromJsonStatesLoader::CreateGameObject(Properties::GameObjectProp&prop)
{
	if(prop.Type=="button")
	{
		auto button= std::make_shared<Button>(_renderer, _inputHandler, _textureManager);
		button->SetPosition({ static_cast<double>(prop.X),static_cast<double>(prop.Y) });
		button->SetWidth(prop.Width);
		button->SetHeight(prop.Height);
		button->SetName(prop.Name);
		button->SetTextureName(prop.TextureName);
		button->SetColumnsCount(prop.Columns);
		button->SetFramesCount(prop.FramesCount);
		
		return button;
	}
	if(prop.Type=="title")
	{
		return nullptr;
	}
	return nullptr;
}

std::vector<std::shared_ptr<GameObject>>FromJsonStatesLoader::ParseGameObjects(nlohmann::basic_json<>json)
{
	std::vector<std::shared_ptr<GameObject>>gameObjects;
	for(auto&gameObject:json)
	{
		Properties::GameObjectProp prop;
		prop = gameObject;
		std::shared_ptr<GameObject>object = CreateGameObject(prop);
		gameObjects.emplace_back(object);
	}
	return gameObjects;
}
