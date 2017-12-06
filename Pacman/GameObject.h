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

	int _currentFrame;

	int _framesCount;

	int _columnsCount;
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

	virtual int GetCurrentFrame() const
	{
		return _currentFrame;
	}

	virtual void SetCurrentFrame(int currentFrame)
	{
		_currentFrame = currentFrame;
	}

	virtual int GetFramesCount() const
	{
		return _framesCount;
	}

	virtual void SetFramesCount(int framesCount)
	{
		_framesCount = framesCount;
	}

	virtual int GetColumnsCount() const
	{
		return _columnsCount;
	}

	virtual void SetColumnsCount(int columnsCount)
	{
		_columnsCount = columnsCount;
	}

	GameObject();
	~GameObject();
};

