#pragma once
#include "IDrawable.h"
#include "IMovable.h"

class GameObject:public IDrawable
{
protected:
	std::pair<int, int>_position;
	int _width;
	int _height;
public:
	virtual void Update() = 0;

	virtual const std::pair<int,int>& GetPosition()const;

	virtual void SetPostion(const std::pair<int, int>&newPos);

	virtual const int GetWidth()const;
	virtual void SetWidth(int width);

	virtual const int GetHeight()const;
	virtual void SetHeight(int height);

	GameObject();
	~GameObject();
};

