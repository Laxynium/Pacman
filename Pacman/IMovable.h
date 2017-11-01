#pragma once
#include <utility>

struct IMovable
{
	virtual void Move(const std::pair<int,int>& vec) = 0;

	virtual ~IMovable(){}
};

