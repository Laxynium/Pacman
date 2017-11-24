#pragma once
#include "ICollisionManager.h"
#include "Event.h"

class GameLogicHandler
{
	ICollisionManager& _collisionManager;

	void OnPlayerPickedSuperBall(ICollidable&A,ICollidable&B);

	void OnPlayerPickedBall(ICollidable&A, ICollidable&B);

	void OnPlayerGhostCollision(ICollidable&A, ICollidable&B);

	static ICollidable&GetCollidableWith(Tag tag, ICollidable&A, ICollidable&B);

	int _countOfBalls;
	int _countOfPickedBalls=0;

	bool _isSuperBallPicked = false;

	time_t _startTime;

	int _duration = 7000;

	int _numberOfLives = 3;

	int _numberOfScoredPoints = 0;

	int _numberOfGhostsEatenInRow = 0;

public:
	GameLogicHandler(GameLogicHandler&) = delete;
	GameLogicHandler(GameLogicHandler&&) = default;
	GameLogicHandler(ICollisionManager&collisionManager): _collisionManager(collisionManager) 
	{
		_collisionManager.Subscribe(Tag::Player, Tag::SuperBall, [this](auto&A, auto&B) {this->OnPlayerPickedSuperBall(A, B); });

		_collisionManager.Subscribe(Tag::Player, Tag::Pickable, [this](auto&A, auto&B) {this->OnPlayerPickedBall(A, B); });

		_collisionManager.Subscribe(Tag::Player, Tag::Enemy, [this](auto&A, auto&B) {this->OnPlayerGhostCollision(A, B); });
	}

	void Update();

	void SetGameEndPoint(int numberOfBalls);

	Event<ICollidable&>PlayerPickedSuperBall;

	Event<ICollidable&>PlayerPickedBall;

	Event<ICollidable&>PlayerAteGhost;

	Event<void>GhostHitPlayer;

	Event<void>	GameEnded;

	Event<void>DurationOfSuperBallEnded;
};

