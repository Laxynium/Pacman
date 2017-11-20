#include "GameLogicHandler.h"

void GameLogicHandler::OnPlayerPickedSuperBall(ICollidable& A, ICollidable& B)
{
	++_countOfPickedBalls;
	PlayerPickedSuperBall(GetCollidableWith(Tag::SuperBall,A,B));

	if(_countOfPickedBalls>=_countOfBalls)
	{
		GameEnded();
	}

}

void GameLogicHandler::OnPlayerPickedBall(ICollidable& A, ICollidable& B)
{
	++_countOfPickedBalls;
	PlayerPickedBall(GetCollidableWith(Tag::Pickable, A, B));

	if (_countOfPickedBalls >= _countOfBalls)
	{
		GameEnded();
	}

}

ICollidable& GameLogicHandler::GetCollidableWith(Tag tag, ICollidable& A, ICollidable& B)
{
	return A.GetTag() == tag ? A : B;
}

void GameLogicHandler::Update()
{

}

void GameLogicHandler::SetGameEndPoint(int numberOfBalls)
{
	_countOfBalls = numberOfBalls;
}
