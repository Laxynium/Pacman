#pragma once

class IClearable
{
public:
	virtual ~IClearable() = default;
	virtual void Clear() = 0;
};
