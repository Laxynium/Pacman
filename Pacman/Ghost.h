#pragma once
#include "GameObject.h"
#include "IRenderer.h"
#include "ICollisionManager.h"
#include "MoveToPositionBehaviour.h"
#include "ITextureManager.h"
#include "GhostState.h"

class Ghost:public GameObject,public ICollidable
{
	enum class State
	{
		Base, Normal,BackToBase,Scared,Flashing
	};
	State _currentState = State::Base;
	Animation _animation{2,40,0};
	clock_t _changeTextureClock=0;

	IRenderer& _renderer;
	ICollisionManager& _collisionManager;
	ITextureManager& _textureManager;

	Tag _tag=Tag::Enemy;


	Vector2D _direction = { 1,0 };
	int _speed = 2;
	Vector2D _velocity = {};
	Vector2D _startPosition = {};
	bool _isStartPositionInitialized = false;

	std::vector<std::unique_ptr<BehaviourBase>>_behaviours;
	BehaviourBase * _currentBehaviour;


	std::string _eyesTextureName;
	std::string _whiteTextureName;
	std::string _eatableTextureName;
	std::string _currentTexture;


	int _framesOffset = 0;


private://methods
	void OnLeaveBase();

	void OnReturnToBase();

	void SetupBehaviours();

	void OnStateChanged();

	void IncreaseVelocity();

	void SetupDefaultValues();

	void SetVelocity(const Vector2D& velocity);

public:
	Ghost(IRenderer& renderer, ICollisionManager& collisionManager,ITextureManager&textureManager);

	void Draw() override;

	void Update() override;

	Rect GetAreaOfCollision() const override;

	Tag GetTag() const override;

	void SetPosition(const Vector2D& newPos) override;

	void SetTag(Tag tag);


	const Vector2D& GetVelocity() const;

	const Vector2D& GetDirection() const;

	void SetDirection(const Vector2D& direction);

	int GetSpeed();

	void OnPlayerPickedUpSuperBall(ICollidable&superBall);
	void OnSuperBallPowerEnding();

	void OnEndDurationsOfSuperBall();

	void OnBeingEaten(ICollidable&ghost);

	void OnHitPlayer();


	void SetEyesTextureName(const std::string& eyesTextureName);
	void SetWhiteTextureName(const std::string& whiteTextureName);
	void SetEatableTextureName(const std::string& eatableTextureName);
	void SetTextureName(const std::string& textureName) override;
};
