#pragma once
#include <memory>
#include <string>
#include "ILayerParser.h"
#include "Tileset.h"
#include "LayerParsersCreator.h"

class ILayerParsersCreator
{
public:
	virtual std::unique_ptr<ILayerParser>Create(const std::string&type) = 0;

	//virtual void AddTilesets(const std::vector<Test::Tileset>& tilesets) = 0;

	virtual ~ILayerParsersCreator() {}
};

