#include "GameLogicHandler.h"
#include <ctime>

void GameLogicHandler::OnPlayerPickedSuperBall(ICollidable& A, ICollidable& B)
{
	++_countOfPickedBalls;

	auto &ball = GetCollidableWith(Tag::SuperBall, A, B);

	PlayerPickedSuperBall(ball);

	_collisionManager.Deregister(ball);

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
		PlayerAteGhost(GetCollidableWith(Tag::Enemy,A,B));
	}
	else
	{
		--_numberOfLives;

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
