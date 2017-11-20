#include "GameLogicHandler.h"

void GameLogicHandler::OnPlayerPickedSuperBall(ICollidable& A, ICollidable& B)
{
	PlayerPickedSuperBall(GetCollidableWith(Tag::SuperBall,A,B));
}

ICollidable& GameLogicHandler::GetCollidableWith(Tag tag, ICollidable& A, ICollidable& B)
{
	return A.GetTag() == tag ? A : B;
}
