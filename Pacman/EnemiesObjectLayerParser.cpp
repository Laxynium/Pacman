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
	std::string TextureName;
	std::string TexturePath;
	int ColumnsCount;
	int FramesCount;
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

		auto properties = ghost.at("properties");

		prop.TextureName = properties.at("textureName").get<std::string>();
		prop.TexturePath = properties.at("texturePath").get<std::string>();
		prop.ColumnsCount = properties.at("columnsCount").get<int>();
		prop.FramesCount = properties.at("framesCount").get<int>();
		ghostProperties.emplace_back(prop);
	}
}
#endif


EnemiesObjectLayerParser::EnemiesObjectLayerParser(Factory&factory, ICollisionManager&collisionManager, GameLogicHandler&gameLogicHandler, ITextureManager&textureManager) :_factory(factory), _collisionManager(collisionManager), _gameLogicHandler(gameLogicHandler), _textureManager(textureManager)
{
}

std::unique_ptr<LayerBase> EnemiesObjectLayerParser::Parse(nlohmann::basic_json<> json)
{
	auto enemiesObjectLayer = std::make_unique<EnemiesObjectLayer>(json["name"].get<std::string>(),_collisionManager);

	const auto tagName=json["properties"]["tag"].get<std::string>();

	auto tag=EnumParser<Tag>().ParseSomeEnum(tagName);

	auto properties=json.at("properties");

	const auto whiteGhostTexturePath = properties["whiteTexturePath"].get<std::string>();
	const auto whiteGhostTextureName=properties["whiteTextureName"].get<std::string>();

	const auto eatableGhostTexturePath = properties["eatableTexturePath"].get<std::string>();
	const auto eatableGhostTextureName = properties["eatableTextureName"].get<std::string>();

	const auto eyesTexturePath = properties["eyesTexturePath"].get<std::string>();
	const auto eyesTextureName = properties["eyesTextureName"].get<std::string>();

	_textureManager.LoadTextureFromFile(whiteGhostTexturePath, whiteGhostTextureName);
	_textureManager.LoadTextureFromFile(eatableGhostTexturePath, eatableGhostTextureName);
	_textureManager.LoadTextureFromFile(eyesTexturePath, eyesTextureName);

	std::vector<GhostProperites> ghostProperiteses = json.at("objects");


	std::vector<std::shared_ptr<GameObject>>ghosts;
	for(auto&ghostProp:ghostProperiteses)
	{
		_textureManager.LoadTextureFromFile(ghostProp.TexturePath, ghostProp.TextureName);

		auto ghost=std::shared_ptr<Ghost>(_factory.CreateGhost());

		ghost->SetPosition(ghostProp.Position);
		ghost->SetWidth(ghostProp.Width);
		ghost->SetHeight(ghostProp.Height);
		ghost->SetTag(tag);
		ghost->SetTextureName(ghostProp.TextureName);
		ghost->SetColumnsCount(ghostProp.ColumnsCount);
		ghost->SetFramesCount(ghostProp.FramesCount);
		ghost->SetCurrentFrame(0);

		ghost->SetEatableTextureName(eatableGhostTextureName);
		ghost->SetEyesTextureName(eyesTextureName);
		ghost->SetWhiteTextureName(whiteGhostTextureName);

		//TODO bind here controlers to proper ghosts
		_collisionManager.Register(*ghost);

		_gameLogicHandler.PlayerPickedSuperBall += std::bind(&Ghost::OnPlayerPickedUpSuperBall, ghost.get(), std::placeholders::_1);

		_gameLogicHandler.DurationOfSuperBallEnded += std::bind(&Ghost::OnEndDurationsOfSuperBall, ghost.get());

		_gameLogicHandler.SuperBallPowerIsAboutToEnd += std::bind(&Ghost::OnSuperBallPowerEnding, ghost.get());

		_gameLogicHandler.PlayerAteGhost += std::bind(&Ghost::OnBeingEaten, ghost.get(),std::placeholders::_1);

		_gameLogicHandler.GhostHitPlayer += std::bind(&Ghost::OnHitPlayer, ghost.get());

		ghosts.emplace_back(ghost);
	}

	enemiesObjectLayer->SetGameObjects(ghosts);

	return enemiesObjectLayer;
}
