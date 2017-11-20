#include "BallObjectLayerParser.h"
#include "BallsObjectLayer.h"

BallObjectLayerParser::BallObjectLayerParser(Factory&factory,ICollisionManager&collisionManager) :
	 _factory(factory), _collisionManager(collisionManager)
{
}

#ifndef BALLPROPS
#define BALLPROPS
using nlohmann::json;

struct BallProperties
{
	int Width;
	int Height;
	Vector2D Posistion;
	Tag Tag;
};
namespace std
{
	void from_json(const json& j, std::vector<BallProperties>&ballProperties)
	{
		for (auto&obj : j)
		{
			BallProperties properties;
			properties.Width = obj.at("width").get<int>();
			properties.Height = obj.at("height").get<int>();
			properties.Posistion.SetX(obj.at("x").get<int>());
			properties.Posistion.SetY(obj.at("y").get<int>());

			properties.Tag= EnumParser<Tag>().ParseSomeEnum(obj.at("properties").at("tag").get<std::string>());

			ballProperties.emplace_back(properties);
		}
	}
}
#endif

std::unique_ptr<LayerBase> BallObjectLayerParser::Parse(nlohmann::basic_json<> json)
{
	auto objectLayer = std::make_unique<BallsObjectLayer>(json["name"].get<std::string>());


	std::vector<BallProperties>ballProperties = json.at("objects");

	std::vector<std::shared_ptr<GameObject>>gameObjects;

	for (auto&balProp : ballProperties)
	{
		auto ball = _factory.CreateBall(balProp.Posistion, balProp.Width, balProp.Height);

		ball->SetTag(balProp.Tag);

		_collisionManager.Register(*ball);

		gameObjects.emplace_back(ball);
	}

	objectLayer->SetGameObjects(gameObjects);


	//objectLayer->SubscribeTo(_collisionManager);
	
	return objectLayer;
}
