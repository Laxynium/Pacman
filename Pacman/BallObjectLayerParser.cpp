#include "BallObjectLayerParser.h"
#include "BallsObjectLayer.h"
#include "GameLogicHandler.h"

BallObjectLayerParser::BallObjectLayerParser(Factory&factory,ICollisionManager&collisionManager,GameLogicHandler&gameLogicHandler) :
	 _factory(factory), _collisionManager(collisionManager), _gameLogicHandler(gameLogicHandler)
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
	auto ballsObjectLayer = std::make_unique<BallsObjectLayer>(json["name"].get<std::string>(),_collisionManager);


	std::vector<BallProperties>ballProperties = json.at("objects");

	std::vector<std::shared_ptr<GameObject>>gameObjects;

	for (auto&balProp : ballProperties)
	{
		auto ball = _factory.CreateBall(balProp.Posistion, balProp.Width, balProp.Height);

		ball->SetTag(balProp.Tag);

		_collisionManager.Register(*ball);

		gameObjects.emplace_back(ball);
	}

	_gameLogicHandler.SetGameEndPoint(ballProperties.size());

	ballsObjectLayer->SetGameObjects(gameObjects);

	_gameLogicHandler.PlayerPickedSuperBall += std::bind(&BallsObjectLayer::OnCollisionSuperBallWithPlayer, ballsObjectLayer.get(), std::placeholders::_1);

	_gameLogicHandler.PlayerPickedBall	+= std::bind(&BallsObjectLayer::OnCollisionWithPlayer, ballsObjectLayer.get(), std::placeholders::_1);
	

	return ballsObjectLayer;
}
