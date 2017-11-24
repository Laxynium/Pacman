#include "GameLogicHandler.h"
#include <ctime>
#include <iostream>

void GameLogicHandler::OnPlayerPickedSuperBall(ICollidable& A, ICollidable& B)
{
	++_countOfPickedBalls;

	auto &ball = GetCollidableWith(Tag::SuperBall, A, B);

	PlayerPickedSuperBall(ball);

	_collisionManager.Deregister(ball);

	//TODO move to ScoreHandler
	_numberOfScoredPoints += 50;
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

	PlayerPickedBall(ball);

	_collisionManager.Deregister(ball);

	//TODO move to ScoreHandler
	_numberOfScoredPoints += 10;
	std::cout << "Score " << _numberOfScoredPoints << std::endl;

	if (_countOfPickedBalls >= _countOfBalls)
	{
		GameEnded();
	}
}

void GameLogicHandler::OnPlayerGhostCollision(ICollidable& A, ICollidable& B)
{
	//TODO calculate things required to score points

	if(_isSuperBallPicked)
	{
		_numberOfScoredPoints += 200 * (++_numberOfGhostsEatenInRow);
		std::cout << "Score " << _numberOfScoredPoints << std::endl;
		PlayerAteGhost(GetCollidableWith(Tag::Enemy,A,B));
	}
	else
	{
		--_numberOfLives;
		std::cout << "Actuall count of lives "<<_numberOfLives << std::endl;
		if (_numberOfLives <= 0)
			GameEnded();

		GhostHitPlayer();
	}

}

ICollidable& GameLogicHandler::GetCollidableWith(Tag tag, ICollidable& A, ICollidable& B)
{
	return A.GetTag() == tag ? A : B;
}

void GameLogicHandler::Update()
{
	if(_isSuperBallPicked&&clock()-_startTime>=_duration)
	{
		DurationOfSuperBallEnded();
		_isSuperBallPicked=false;
	}
}

void GameLogicHandler::SetGameEndPoint(int numberOfBalls)
{
	_countOfBalls = numberOfBalls;
}
