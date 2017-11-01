#pragma once
#include "Rect.h"

class ICollidable
{
public:
	virtual Rect GetAreaOfCollision()const = 0;
	virtual ~ICollidable(){}
};
