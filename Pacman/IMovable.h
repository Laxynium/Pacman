#pragma once
#include <utility>
#include "Vector2D.h"

struct IMovable
{
	virtual void Move(const Vector2D& vec) = 0;

	virtual ~IMovable(){}
};

