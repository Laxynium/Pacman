#pragma once
#include <memory>
#include "Level.h"
#include <string>

struct ILevelLoader
{
	virtual std::unique_ptr<Level> LoadLevel(const std::string&fileName) = 0;

	virtual ~ILevelLoader() {};
};

