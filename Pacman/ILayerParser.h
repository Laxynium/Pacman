#pragma once
#include "JsonParser.h"
#include "LayerBase.h"

class ILayerParser
{
public:
	virtual ~ILayerParser() {}
	virtual std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) = 0;
};
