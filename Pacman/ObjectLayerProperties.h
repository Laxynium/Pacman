#pragma once
#include <string>
#include <vector>
#include "GameObject.h"
#include <memory>
#include "Tag.h"

namespace Properties
{
	class ObjectLayerProperties
	{
	private:
		std::vector<std::shared_ptr<GameObject>>_objects;
	public:
		std::string Name;

		std::string TextureSource;

		std::string TextureName;

		std::string ObjectsCount;

		Tag Tag;

		const std::vector<std::shared_ptr<GameObject>>& Objects()const
		{
			return _objects;
		}

		void SetObjects(const std::vector<std::shared_ptr<GameObject>>& objects)
		{
			_objects = objects;
		}
	};
}

