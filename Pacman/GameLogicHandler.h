#pragma once
#include "ICollisionManager.h"
#include "Event.h"

class GameLogicHandler:public IUpdateable,public IClearable
{
	ICollisionManager& _collisionManager;

	void OnPlayerPickedSuperBall(ICollidable&A,ICollidable&B);

	void OnPlayerPickedBall(ICollidable&A, ICollidable&B);

	void OnPlayerGhostCollision(ICollidable&A, ICollidable&B);

	static ICollidable&GetCollidableWith(Tag tag, ICollidable&A, ICollidable&B);

	int _countOfBalls;
	int _countOfPickedBalls=0;

	bool _isSuperBallPicked = false;

	bool _isFlashingStarted = false;

	time_t _startTime;

	int _duration = 7000;

	int _startFlashingTime = 5000;

	int _numberOfLives = 3;

	int _numberOfScoredPoints = 0;

	int _numberOfGhostsEatenInRow = 0;

public:
	GameLogicHandler(GameLogicHandler&) = delete;
	GameLogicHandler(GameLogicHandler&&) = default;
	GameLogicHandler(ICollisionManager& collisionManager);

	void Update() override;

	void SetGameEndPoint(int numberOfBalls);

	Event<ICollidable&>PlayerPickedSuperBall;

	Event<ICollidable&>PlayerPickedBall;

	Event<ICollidable&>PlayerAteGhost;

	Event<void>GhostHitPlayer;

	Event<void>	GameEnded;

	Event<void> LevelEnded;

	Event<void>DurationOfSuperBallEnded;

	Event<void>SuperBallPowerIsAboutToEnd;

	Event<int>PlayerScoreChanged;

	Event<int>PlayerLivesChanged;

	void Clear()override;

};

