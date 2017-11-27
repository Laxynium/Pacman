#include "MoveToPositionBehaviour.h"
#include "Ghost.h"
#include <algorithm>
MoveToPositionBehaviour::MoveToPositionBehaviour(ICollisionManager& collisionManager):BehaviourBase(collisionManager)
{
}

void MoveToPositionBehaviour::SetDestination(Vector2D destination)
{
	_destination = destination;
	SetPriorites();
}
bool MoveToPositionBehaviour::IsCollision(const Vector2D&vector)
{
	auto oldPos = _ghost->GetPosition();

	_ghost->SetPosition(oldPos + vector);

	bool collided = _collisionManager.DetectCollision(*_ghost, Tag::Wall);

	_ghost->SetPosition(oldPos);

	return collided;
}

std::vector<MoveToPositionBehaviour::Direction> MoveToPositionBehaviour::GetPosibleDirections()
{
	std::vector<Direction>posibleDirections;
	Vector2D newVelo = Vector2D{ 1,0 }*_ghost->GetSpeed();
	if (!IsCollision(newVelo))
		posibleDirections.emplace_back(Right);
	else
	{
		newVelo = Vector2D{ 1,0 };
		if (!IsCollision(newVelo))
			posibleDirections.emplace_back(Right);
	}

	newVelo = Vector2D{ -1,0 }*_ghost->GetSpeed();
	if (!IsCollision(newVelo))
		posibleDirections.emplace_back(Left);
	else
	{
		newVelo = Vector2D{ -1,0 };
		if (!IsCollision(newVelo))
			posibleDirections.emplace_back(Left);
	}

	newVelo=Vector2D{0,1}*_ghost->GetSpeed();
	if (!IsCollision(newVelo))
		posibleDirections.emplace_back(Down);
	else
	{
		//Try with greater precision
		newVelo = Vector2D{ 0,1 };
		if (!IsCollision(newVelo))
			posibleDirections.emplace_back(Down);
	}

	newVelo = Vector2D{ 0,-1 }*_ghost->GetSpeed();
	if (!IsCollision(newVelo))
		posibleDirections.emplace_back(Up);
	else
	{
		//Try with greater precision
		newVelo = Vector2D{ 0,-1 };
		if (!IsCollision(newVelo))
			posibleDirections.emplace_back(Up);
	}

	return posibleDirections;
}

bool MoveToPositionBehaviour::Contains(std::vector<Direction>directiones, Direction dir)
{
	auto itr=std::find(std::begin(directiones), std::end(directiones), dir);

	return itr != std::end(directiones);
}

MoveToPositionBehaviour::Direction MoveToPositionBehaviour::GetDirectionFromVector(const Vector2D&vec)
{
	if (vec.X() > 0)
		return Right;
	else if (vec.X() < 0)
		return Left;
	else if (vec.Y() > 0)
		return Down;
	else if (vec.Y() < 0)
		return Up;
}

Vector2D MoveToPositionBehaviour::GetVectorFromDirection(Direction dir)
{
	Vector2D vector;
	if(dir==Left)
	{
		vector = { -1,0 };
	}
	else if (dir == Right)
	{
		vector = { 1,0 };
	}
	else if (dir == Up)
	{
		vector = { 0,-1 };
	}
	else if (dir == Down)
	{
		vector = { 0,1};
	}
	return vector*_ghost->GetSpeed();
}

void MoveToPositionBehaviour::MoveGhost(Direction dir)
{
	auto vec=GetVectorFromDirection(dir);
	auto oldPos = _ghost->GetPosition();
	_ghost->SetPosition(oldPos + vec);
	OnTransition(_ghost->GetPosition());
}

void MoveToPositionBehaviour::SetGhostVelo(Direction dir)
{
	auto vec=GetVectorFromDirection(dir);

	_ghost->SetVelocity(vec);
}

MoveToPositionBehaviour::Direction MoveToPositionBehaviour::GetOpposite(Direction dir)
{
	if (dir == Left)return Right;
	if (dir == Right)return Left;
	if (dir == Up)return Down;
	if (dir == Down)return Up;
}

MoveToPositionBehaviour::Direction MoveToPositionBehaviour::GetSwitched(Direction dir)
{
	if (dir == Left)return Up;
	if (dir == Right)return Down;
	if (dir == Up)return Right;
	if (dir == Down)return Left;
}

void MoveToPositionBehaviour::SetPriorites()
{
	Vector2D diffrence= _destination - _ghost->GetPosition();

	if(abs(diffrence.X())>abs(diffrence.Y()))
	{
		auto direction=GetDirectionFromVector({diffrence.X(),0});

		_actualPriority = direction;

		_secondPriority = GetDirectionFromVector({ 0,diffrence.Y() });
	}else
	{
		auto direction = GetDirectionFromVector({ diffrence.X(),0 });

		_secondPriority = direction;

		_actualPriority = GetDirectionFromVector({ 0,diffrence.Y() });
	}

}

void MoveToPositionBehaviour::CheckIfReachedToDestination()
{
	Vector2D diffrenece = _destination - _ghost->GetPosition();
	diffrenece.SetX(abs(diffrenece.X()));
	diffrenece.SetY(abs(diffrenece.Y()));
	if (diffrenece.X()<2&&diffrenece.Y()<2)
	{
		ReachedToDestination();
	}
}

void MoveToPositionBehaviour::Update()
{
	auto posibleDirections = GetPosibleDirections();
	
	auto currentDirection = GetDirectionFromVector(_ghost->GetVelocity());

	auto contains = std::bind(&MoveToPositionBehaviour::Contains,this, posibleDirections, std::placeholders::_1);

	//If is posible move with bigger priority 
	if(_actualPriority!=currentDirection&&GetOpposite(currentDirection)!=_actualPriority)	
		if(contains(_actualPriority))
		{
			MoveGhost(_actualPriority);
			SetGhostVelo(_actualPriority);
			SetPriorites();
			CheckIfReachedToDestination();
			return;
		}

	if(_secondPriority!=currentDirection&&GetOpposite(currentDirection)!=_secondPriority)
		if (contains(_secondPriority))
		{
			MoveGhost(_secondPriority);
			SetGhostVelo(_secondPriority);
			SetPriorites();
			CheckIfReachedToDestination();
			return;
		}

	//If current dir is available then continue move with it
	if(contains(currentDirection))
	{
		MoveGhost(currentDirection);
		SetGhostVelo(currentDirection);
		SetPriorites();
		CheckIfReachedToDestination();
		return;
	}

	auto switchDirection = GetSwitched(currentDirection);
	if(contains(switchDirection))
	{
		MoveGhost(switchDirection);
		SetGhostVelo(switchDirection);
		SetPriorites();
		CheckIfReachedToDestination();
		return;
	}

	switchDirection = GetOpposite(switchDirection);
	if (contains(switchDirection))
	{
		MoveGhost(switchDirection);
		SetGhostVelo(switchDirection);
		SetPriorites();
		CheckIfReachedToDestination();
		return;
	}

	auto opposite = GetOpposite(currentDirection);
	if(contains(opposite))
	{
		MoveGhost(opposite);
		SetGhostVelo(opposite);
		SetPriorites();
		CheckIfReachedToDestination();
		return;
	}

}
