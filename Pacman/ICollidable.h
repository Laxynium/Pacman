#pragma once
#include "Rect.h"
#include "Tag.h"

class ICollidable
{
public:
	virtual Rect GetAreaOfCollision()const = 0;

	virtual Tag GetTag()const = 0;

	virtual ~ICollidable(){}
};
