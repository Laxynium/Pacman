#pragma once
#include "ObjectLayer.h"

class BallsObjectLayer:public ObjectLayer
{
protected:
	std::unique_ptr<Properties::ObjectLayerProperties>_properties;
	void OnCollisionBetweenPickerAndPickable(ICollidable&objectA, ICollidable&objectB);
public:
	BallsObjectLayer(const std::string& type, GameLogicHandler& gameLogicHandler);

	const std::unique_ptr<Properties::ObjectLayerProperties>& Properties() const;

	void SetProperties(Properties::ObjectLayerProperties&& object_layer_properties);


	std::vector<std::shared_ptr<GameObject>>& GameObjects();

	void SetGameObjects(const std::vector<std::shared_ptr<GameObject>>& sharedPtrs);

	void SubscribeTo(ICollisionManager&collisionManager);

	void Update() override;

};
