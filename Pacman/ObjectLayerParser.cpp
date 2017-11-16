#include "ObjectLayerParser.h"
#include "ObjectLayer.h"
#include "ObjectLayerProperties.h"
#include "Ball.h"
using nlohmann::json;
struct BallProperties
{
	int Width;
	int Height;
	std::pair<int,int> Posistion;
};
namespace std
{
		void from_json(const json& j, std::vector<BallProperties>&ballProperties)
		{
			for(auto&obj:j)
			{
				BallProperties properties;
				properties.Width = obj.at("width").get<int>();
				properties.Height = obj.at("height").get<int>();
				properties.Posistion.first = obj.at("x").get<int>();
				properties.Posistion.second = obj.at("y").get<int>();
				ballProperties.emplace_back(properties);
			}
		}
}

ObjectLayerParser::ObjectLayerParser(ICollisionManager& collisionManager, 
										GameLogicHandler &gameLogicHandler, Factory&factory):
											_collisionManager(collisionManager), _gameLogicHandler(gameLogicHandler), _factory(factory)
{
}

std::unique_ptr<LayerBase> ObjectLayerParser::Parse(nlohmann::basic_json<> json)
{
	auto objectLayer = std::make_unique<ObjectLayer>(json["type"].get<std::string>(),_gameLogicHandler);

	Properties::ObjectLayerProperties objectLayerProperties;
	objectLayerProperties.Name=json["name"].get<std::string>();
	

	auto propertiesJson = json["properties"];
	objectLayerProperties.TextureSource= propertiesJson["texture"].get<std::string>();
	objectLayerProperties.TextureName= propertiesJson["textureName"].get<std::string>();
	objectLayerProperties.ObjectsCount = propertiesJson["ballCount"].get<int>();

	const auto tagName = propertiesJson["tag"];

	EnumParser<Tag> parser;
	objectLayerProperties.Tag=parser.ParseSomeEnum(tagName);

	objectLayer->SetProperties(std::move(objectLayerProperties));

	std::vector<BallProperties>ballProperties=json.at("objects");
	std::vector<std::shared_ptr<GameObject>>gameObjects;
	for (auto&balProp : ballProperties)
	{
		auto ball = _factory.CreateBall(balProp.Posistion, balProp.Width, balProp.Height);

		_collisionManager.Register(*ball);

		gameObjects.emplace_back(ball);
	}		

	objectLayer->SetGameObjects(gameObjects);

	objectLayer->SubscribeTo(_collisionManager);

	return objectLayer;
}
