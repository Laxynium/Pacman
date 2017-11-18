#pragma once
#include "IInnerObjectLayerParser.h"

class IInnerObjectLayerParsersCreator
{
public:
	virtual ~IInnerObjectLayerParsersCreator() = default;
	virtual std::unique_ptr<IInnerObjectLayerParser> Create(const std::string& type)=0;
};
