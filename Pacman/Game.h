#pragma once
#include <memory>
#include "BoostDI.h"
#include "IInputHandler.h"
#include <memory>
#include "IRenderer.h"
#include "Square.h"
#include "BoostDI.h"
#include "ITextureManager.h"
#include "ILevelLoader.h"
#include "Ball.h"
namespace di=boost::di;
class Game
{
	std::unique_ptr<IInputHandler> _input_handler;

	std::shared_ptr<IRenderer> _renderer;

	bool _isRunning = true;

	std::unique_ptr<MoveableGameObject> drawable;
	std::unique_ptr<MoveableGameObject> drawable2;

	std::shared_ptr<ILevelLoader> _levelLoader;

	shared_ptr<ICollisionManager> _collisionManager;

	std::vector<std::unique_ptr<GameObject>>_balls;

	unique_ptr<Level> _level;

public:
	Game(std::shared_ptr<IRenderer> renderer ,std::unique_ptr<IInputHandler> inputHandler,std::shared_ptr<ILevelLoader>levelLoader,
			shared_ptr<ICollisionManager>collisionManager);

	Game(Game&& other) noexcept = default;

	~Game() = default;

	bool IsRunning() const;

	void HandleInput();

	void Update() const;
	
	void Render() const;
private:
	void BindInput();
};

