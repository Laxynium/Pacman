#pragma once
#include "IUpdateable.h"
#include "Vector2D.h"
#include "ICollisionManager.h"
#include "BehaviourBase.h"
#include <list>
#include "Event.h"
class Ghost;

class MoveToPositionBehaviour:public BehaviourBase
{
	enum  Direction
	{
		Left, Right, Up, Down
	};
	Vector2D _destination;
	Direction _actualPriority=Right;
	Direction _secondPriority = Up;
	std::vector<Direction> GetPosibleDirections();
	bool Contains(std::vector<Direction> directiones, Direction dir);
	Direction GetDirectionFromVector(const Vector2D& vec);
	Vector2D GetVectorFromDirection(Direction dir);
	void MoveGhost(Direction dir);
	void SetGhostVelo(Direction dir);
	Direction GetOpposite(Direction dir);
	Direction GetSwitched(Direction dir);
	void SetPriorites();
	void CheckIfReachedToDestination();
public:
	MoveToPositionBehaviour(ICollisionManager& collisionManager);
	void SetDestination(Vector2D destination);
	bool IsCollision(const Vector2D& vector);
	void Update() override;
	Event<void>ReachedToDestination;
};
