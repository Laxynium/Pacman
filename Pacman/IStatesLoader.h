#pragma once
#include <memory>
#include <vector>
#include "IGameState.h"

class IStatesLoader
{
public:
	virtual ~IStatesLoader() = default;

	virtual void Load(const std::string& fileName,std::shared_ptr<IGameState>state) = 0;
};
