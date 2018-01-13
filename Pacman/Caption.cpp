#include "Caption.h"
#include "Rect.h"

void Caption::Draw()
{
	int x = (_currentFrame%_columnsCount)*(_width);
	int y = (_currentFrame / _columnsCount) * _height;
	_renderer->CopyEx(_textureManager->FindTexture(_textureName), &Rect{ x,y,_width,_height }, &Rect{ static_cast<int>(_position.X()),static_cast<int>(_position.Y()),_width,_height });
}

void Caption::Update()
{
	clock_t currentTime = clock();

	if (currentTime - _animClock >= _animDelay)
	{
		++_currentFrame %= _framesCount;
		_animClock = currentTime;
	}
}
