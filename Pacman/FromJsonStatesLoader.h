#pragma once
#include "IStatesLoader.h"
#include "JsonParser.h"
#include "Button.h"
namespace Properties
{
	struct GameObjectProp;

}
class FromJsonStatesLoader:public IStatesLoader
{
	std::shared_ptr<ITextureManager> _textureManager;
	std::shared_ptr<IInputHandler> _inputHandler;
	std::shared_ptr<IRenderer> _renderer;

private://methods
	std::vector<std::shared_ptr<GameObject>>FromJsonStatesLoader::ParseGameObjects(nlohmann::basic_json<>json);
	void ParseAndLoadTextures(nlohmann::basic_json<>json);
	std::shared_ptr<GameObject> CreateGameObject(Properties::GameObjectProp& prop);
public:
	FromJsonStatesLoader(std::shared_ptr<IRenderer>renderer,std::shared_ptr<IInputHandler>inputHandler,std::shared_ptr<ITextureManager> textureManager);
	void Load(const std::string& fileName,std::shared_ptr<IGameState>state) override;
};
