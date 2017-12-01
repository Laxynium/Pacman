#include "IGameState.h"

const std::string& IGameState::GetStateName()
{
	return _stateName;
}

IGameState& IGameState::SetStateName(const std::string& name)
{
	_stateName = name;
	return *this;
}
