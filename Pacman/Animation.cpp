#include "Animation.h"

Animation::Animation(int framesCount, int animationDelay): _currentFrame(0), _framesCount(framesCount),
                                                           _animationDelay(animationDelay)
{
	_isPlaying = true;
}

int Animation::GetCurrentFrame() const
{
	return _currentFrame;
}

void Animation::Play()
{
	_isPlaying = true;
}

void Animation::Stop()
{
	_isPlaying = false;
}

void Animation::Update()
{
	if (!_isPlaying)return;

	const clock_t currentTime = clock();

	if(currentTime-_time>=_animationDelay)
	{
		++_currentFrame %= _framesCount;
		_time = currentTime;
	}
}
