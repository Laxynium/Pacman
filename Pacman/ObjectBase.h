#pragma once
#include "IDrawable.h"

class ObjectBase:public IDrawable
{
public:
	virtual void Update() = 0;
};
