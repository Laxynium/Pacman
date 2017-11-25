#pragma once
#include "IMovable.h"
#include "ObjectBase.h"
#include "Vector2D.h"

class GameObject:public ObjectBase
{
protected:
	Vector2D _position;
	int _width;
	int _height;
public:

	virtual const Vector2D& GetPosition() const;

	virtual void SetPosition(const Vector2D& newPos);

	virtual const int GetWidth()const;
	virtual void SetWidth(int width);

	virtual const int GetHeight()const;
	virtual void SetHeight(int height);

	GameObject();
	~GameObject();
};

