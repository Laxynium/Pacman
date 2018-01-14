#include "SDLInputHandler.h"
#include <SDL.h>
#include <map>
#include <functional>
#include <iostream>
#include "SDLActionType.h"
#include <algorithm>
#include "SpecialSDLActionType.h"
#include "MouseMoveActionArg.h"
#include "SDLActiveButtonsActionType.h"
#include "ActiveKeysActionArg.h"

auto SDLInputHandler::SpecialActions()
{
	decltype(_actions) specialActions;
	std::copy_if(_actions.begin(), _actions.end(), std::back_inserter(specialActions), [](const auto&pair)
	{
		SpecialSDLActionType* actionType = dynamic_cast<SpecialSDLActionType*>(pair.first);

		if (actionType == nullptr)return false;

		return true;
	});
	return specialActions;
}

auto SDLInputHandler::SDLActions()
{
	decltype(_actions) sdlActions;
	std::copy_if(_actions.begin(), _actions.end(), std::back_inserter(sdlActions), [](const auto&pair)
	{
		SDLActionType* actionType = dynamic_cast<SDLActionType*>(pair.first);

		if (actionType == nullptr)return false;

		return true;
	});
	return sdlActions;
}

void SDLInputHandler::HandleActions()
{
	int length;
	const auto keyStates = SDL_GetKeyboardState(&length);
	
	auto keyboardActions = SpecialActions();

	for (auto &action : keyboardActions)
	{
		SpecialSDLActionType*actionType = dynamic_cast<SpecialSDLActionType*>(action.first);

		if (keyStates[actionType->KeyCode])
			if (action.second != nullptr)
			{
				action.second();
			}			
	}
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{	
		auto result=FindActions(_actions,[&](const auto&pair)
		{
			SDLActionType* actionType = dynamic_cast<SDLActionType*>(pair.first);

			if (actionType == nullptr)return false;

			if (actionType->eventType == event.type)
				return true;
		});
		for(auto&action:result)
		{
			action.second();
		}

		auto result2=FindActions<std::shared_ptr<ActionArg>>(_actionsWithParams,[&](const auto&pair)
		{
			SDLActionType* actionType = dynamic_cast<SDLActionType*>(pair.first);

			if (actionType == nullptr)return false;

			if (actionType->eventType == event.type)
			{
				return true;
			}
			return false;
		});

		for(auto&action:result2)
		{
			SDLActionType* actionType = dynamic_cast<SDLActionType*>(action.first);

			if (actionType->eventType == SDL_MOUSEMOTION)
			{
				action.second(std::make_shared<MouseMoveActionArg>(event.motion.x, event.motion.y));
			}		
		}
		

		auto result3 = FindActions<std::shared_ptr<ActionArg>>(_actionsWithParams, [&](const auto&pair)
		{
			SDLActiveButtonsActionType* actionType = dynamic_cast<SDLActiveButtonsActionType*>(pair.first);

			if (actionType == nullptr)return false;

			return true;

		});

		std::vector<std::string>activeKeys;
		for (int i = 0; i < length; ++i)
		{
			if (keyStates[i])
				activeKeys.push_back(SDL_GetScancodeName(static_cast<SDL_Scancode>(i)));
		}

		for (auto&action : result3)
		{
			action.second(std::make_shared<ActiveKeysActionArg>(activeKeys));
		}
	}
}



SDLInputHandler::SDLInputHandler()
{
}
SDLInputHandler::~SDLInputHandler()
{
}
