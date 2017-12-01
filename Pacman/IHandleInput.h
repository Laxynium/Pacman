#pragma once

class IHandleInput
{
public:
	virtual ~IHandleInput() = default;
	virtual void HandleInput() = 0;
};
