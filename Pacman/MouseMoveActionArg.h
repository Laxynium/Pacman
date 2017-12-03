#pragma once
#include "ActionArg.h"

class MouseMoveActionArg:public ActionArg
{
	int _x=0, _y=0;
public:

	MouseMoveActionArg(int x,int y):_x(x),_y(y) {  }

	int GetX() const
	{
		return _x;
	}

	void SetX(const int x)
	{
		_x = x;
	}

	int GetY() const
	{
		return _y;
	}

	void SetY(const int y)
	{
		_y = y;
	}
};
