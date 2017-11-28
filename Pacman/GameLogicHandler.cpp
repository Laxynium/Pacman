#include "GameLogicHandler.h"
#include <ctime>
#include <iostream>

void GameLogicHandler::OnPlayerPickedSuperBall(ICollidable& A, ICollidable& B)
{
	++_countOfPickedBalls;

	auto &ball = GetCollidableWith(Tag::SuperBall, A, B);

	_collisionManager.Deregister(ball);

	PlayerPickedSuperBall(ball);

	_numberOfScoredPoints += 50;
	PlayerScoreChanged(_numberOfScoredPoints);
	std::cout << "Score " << _numberOfScoredPoints << std::endl;

	_numberOfGhostsEatenInRow = 0;

	_isSuperBallPicked = true;

	_startTime = clock();

	if(_countOfPickedBalls>=_countOfBalls)
	{
		GameEnded();
	}

}

void GameLogicHandler::OnPlayerPickedBall(ICollidable& A, ICollidable& B)
{
	++_countOfPickedBalls;

	auto &ball = GetCollidableWith(Tag::Pickable, A, B);

	_collisionManager.Deregister(ball);

	PlayerPickedBall(ball);

	//TODO move to ScoreHandler
	_numberOfScoredPoints += 10;
	PlayerScoreChanged(_numberOfScoredPoints);
	std::cout << "Score " << _numberOfScoredPoints << std::endl;

	if (_countOfPickedBalls >= _countOfBalls)
	{
		LevelEnded();
	}
}

void GameLogicHandler::OnPlayerGhostCollision(ICollidable& A, ICollidable& B)
{
	//TODO calculate things required to score points

	if(_isSuperBallPicked)
	{
		_numberOfScoredPoints += 200 * (++_numberOfGhostsEatenInRow);
		PlayerScoreChanged(_numberOfScoredPoints);
		std::cout << "Score " << _numberOfScoredPoints << std::endl;
		PlayerAteGhost(GetCollidableWith(Tag::Enemy,A,B));
	}
	else
	{
		--_numberOfLives;
		std::cout << "Actuall count of lives "<<_numberOfLives << std::endl;
		if (_numberOfLives <= 0)
			GameEnded();

		PlayerLivesChanged(_numberOfLives);

		GhostHitPlayer();
	}

}

ICollidable& GameLogicHandler::GetCollidableWith(Tag tag, ICollidable& A, ICollidable& B)
{
	return A.GetTag() == tag ? A : B;
}

GameLogicHandler::GameLogicHandler(ICollisionManager& collisionManager): _collisionManager(collisionManager)
{
	_collisionManager.Subscribe(Tag::Player, Tag::SuperBall,
	                            [this](auto& A, auto& B) { this->OnPlayerPickedSuperBall(A, B); });

	_collisionManager.Subscribe(Tag::Player, Tag::Pickable, [this](auto& A, auto& B) { this->OnPlayerPickedBall(A, B); });

	_collisionManager.Subscribe(Tag::Player, Tag::Enemy, [this](auto& A, auto& B) { this->OnPlayerGhostCollision(A, B); });
}

void GameLogicHandler::Update()
{
	if(_isSuperBallPicked&&clock()-_startTime>=_duration)
	{
		DurationOfSuperBallEnded();
		_isSuperBallPicked=false;
		_isFlashingStarted = false;
	}
	if (_isSuperBallPicked&&!_isFlashingStarted&&clock()-_startTime>=_startFlashingTime)
	{
		SuperBallPowerIsAboutToEnd();
		_isFlashingStarted = true;
	}

}

void GameLogicHandler::SetGameEndPoint(int numberOfBalls)
{
	_countOfBalls = numberOfBalls;
}

void GameLogicHandler::Clear()
{
	PlayerPickedSuperBall.Clear();

	PlayerPickedBall.Clear();

	PlayerAteGhost.Clear();

	GhostHitPlayer.Clear();

	GameEnded.Clear();

	LevelEnded.Clear();

	DurationOfSuperBallEnded.Clear();

	SuperBallPowerIsAboutToEnd.Clear();

	PlayerScoreChanged.Clear();

	PlayerLivesChanged.Clear();

	_countOfPickedBalls = 0;

	_isSuperBallPicked = false;

	_isFlashingStarted = false;
}
