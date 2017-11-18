#pragma once
#include "ObjectLayer.h"
#include "JsonParser.h"

class IInnerObjectLayerParser
{
public:
	virtual ~IInnerObjectLayerParser(){}
	virtual std::unique_ptr<LayerBase> Parse(nlohmann::basic_json<> json) = 0;
};

