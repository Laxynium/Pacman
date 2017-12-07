#pragma once
#include "IUpdateable.h"
#include <ctime>

class Animation:public IUpdateable
{
	int _currentFrame;
	int _framesCount;
	int _animationDelay;
	clock_t _time=0;
	bool _isPlaying;
public:
	Animation(int framesCount, int animationDelay);

	virtual int GetCurrentFrame()const;

	virtual void Play();
	virtual void Stop();

	void Update() override;
};
