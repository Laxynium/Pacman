#pragma once
#include "IUpdateable.h"
#include <ctime>

class Animation:public IUpdateable
{
	int _currentFrame;
	int _framesCount = 1;
	int _columnsCount = 1;
	int _frameOffset = 0;
	int _animationDelay=20;
	clock_t _time=0;
	bool _isPlaying;
public:
	Animation(int framesCount, int animationDelay,int frameOffset);

	virtual int GetCurrentFrame()const;

	virtual void Play();
	virtual void Stop();

	void Update() override;


	void SetFrameCount(const int frameCount)
	{
		_framesCount = frameCount;
	}

	void SetFrameOffset(const int frameOffset)
	{
		_frameOffset = frameOffset;
	}
	void SetCurrentFrame(const int currentFrame)
	{
		_currentFrame = currentFrame;
	}

	void SetColumnsCount(int columnsCount)
	{
		_columnsCount = columnsCount;
	}

	int GetFramesCount() const
	{
		return _framesCount;
	}

	int GetColumnsCount() const
	{
		return _columnsCount;
	}
	int GetFrameOffset()const 
	{
		return _frameOffset;
	}
};
