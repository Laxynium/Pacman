#pragma once
#include "IMovable.h"
#include "ObjectBase.h"
#include "Vector2D.h"
#include <string>

class GameObject:public ObjectBase
{
protected:
	Vector2D _position;
	int _width;
	int _height;

	std::string _name;
	std::string _textureName;
public:

	virtual const Vector2D& GetPosition() const;

	virtual void SetPosition(const Vector2D& newPos);

	virtual const int GetWidth()const;
	virtual void SetWidth(int width);

	virtual const int GetHeight()const;
	virtual void SetHeight(int height);

	virtual const std::string&GetName()const
	{
		return _name;
	}
	virtual void SetName(const std::string& name)
	{
		_name = name;
	}

	virtual void SetTextureName(const std::string& textureName)
	{
		this->_textureName = textureName;
	}
	virtual const std::string&GetTextureName()const
	{
		return _textureName;
	}

	GameObject();
	~GameObject();
};

