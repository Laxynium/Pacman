#include "InnerObjectLayerParsersCreator.h"

std::unique_ptr<IInnerObjectLayerParser> InnerObjectLayerParsersCreator::Create(const std::string& type)
{
	return _parsers[type]();
}

