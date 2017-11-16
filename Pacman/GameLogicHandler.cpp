#include "GameLogicHandler.h"

void GameLogicHandler::GameEnded()
{
	if(_onGameEnded!=nullptr)
		_onGameEnded();
}

void GameLogicHandler::SetOnGameEnded( const std::function<void()>& onGameEnded)
{
	_onGameEnded = onGameEnded;
}

//void GameLogicHandler::PlayerWon(std::function<void()>& action)
//{
//}
//
//void GameLogicHandler::PlayerTookUpBall(std::function<void()>& action)
//{
//}
//
//void GameLogicHandler::PlayerCollidedWithEnemy(std::function<void()>& action)
//{
//}
