#include "EnemiesObjectLayerParser.h"
#include <string>
#include "EnemiesObjectLayer.h"
#include "Ghost.h"
#include "Factory.h"
#include "GameLogicHandler.h"
#ifndef GHOSTPROP
#define GHOSTPROP
using nlohmann::json;

struct GhostProperites
{
	Vector2D Position;
	Color Color;
	int Width;
	int Height;
};

void from_json(const json& json, std::vector<GhostProperites>&ghostProperties)
{
	for (auto&ghost : json)
	{
		GhostProperites prop;
		prop.Width=ghost.at("width").get<int>();
		prop.Height=ghost.at("height").get<int>();
		prop.Position={ghost.at("x").get<double>(), ghost.at("y").get<double>()};
		prop.Color = Color::FromHex(ghost.at("properties").at("color").get<std::string>());
		ghostProperties.emplace_back(prop);
	}
}
#endif


EnemiesObjectLayerParser::EnemiesObjectLayerParser(Factory&factory,ICollisionManager&collisionManager,GameLogicHandler&gameLogicHandler):_factory(factory), _collisionManager(collisionManager), _gameLogicHandler(gameLogicHandler)
{
}

std::unique_ptr<LayerBase> EnemiesObjectLayerParser::Parse(nlohmann::basic_json<> json)
{
	auto enemiesObjectLayer = std::make_unique<EnemiesObjectLayer>(json["name"].get<std::string>());

	const auto tagName=json["properties"]["tag"].get<std::string>();

	auto tag=EnumParser<Tag>().ParseSomeEnum(tagName);

	std::vector<GhostProperites> ghostProperiteses = json.at("objects");
	std::vector<std::shared_ptr<GameObject>>ghosts;
	for(auto&ghostProp:ghostProperiteses)
	{
		auto ghost=std::shared_ptr<Ghost>(_factory.CreateGhost());

		ghost->SetPosition(ghostProp.Position);
		ghost->SetWidth(ghostProp.Width);
		ghost->SetHeight(ghostProp.Height);
		ghost->SetColor(ghostProp.Color);
		ghost->SetTag(tag);
		
		//TODO bind here controlers to proper ghosts
		_collisionManager.Register(*ghost);

		_gameLogicHandler.PlayerPickedSuperBall += std::bind(&Ghost::OnPlayerPickedUpSuperBall, ghost.get(), std::placeholders::_1);

		_gameLogicHandler.DurationOfSuperBallEnded += std::bind(&Ghost::OnEndDurationsOfSuperBall, ghost.get());

		_gameLogicHandler.PlayerAteGhost += std::bind(&Ghost::OnBeingAte, ghost.get(),std::placeholders::_1);

		_gameLogicHandler.GhostHitPlayer += std::bind(&Ghost::OnHitPlayer, ghost.get());

		ghosts.emplace_back(ghost);
	}

	enemiesObjectLayer->SetGameObjects(ghosts);

	return enemiesObjectLayer;
}
