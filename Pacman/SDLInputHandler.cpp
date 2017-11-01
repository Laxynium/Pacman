#include "SDLInputHandler.h"
#include <SDL.h>
#include <map>
#include <functional>
#include <iostream>
#include "SDLActionType.h"
#include <algorithm>
#include "SpecialSDLActionType.h"

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
	//TODO somehow refactor it
	const auto keyStates = SDL_GetKeyboardState(nullptr);

	auto keyboardActions = SpecialActions();

	for (auto &action : keyboardActions)
	{
		SpecialSDLActionType*actionType = dynamic_cast<SpecialSDLActionType*>(action.first);

		if (keyStates[actionType->KeyCode])
			if (action.second != nullptr)
				action.second();
	}
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{	
		if(event.type==SDL_QUIT)
		{
			auto OnQuit=std::find_if(_actions.begin(), _actions.end(), [&](const auto&pair)
			{
				SDLActionType* actionType = dynamic_cast<SDLActionType*>(pair.first);

				if (actionType == nullptr)return false;

				if (actionType->eventType == SDL_QUIT)
					return true;

			});

			while(OnQuit!=_actions.end())
			{
				OnQuit->second();
				++OnQuit;
			}
		}
	}
}



SDLInputHandler::SDLInputHandler()
{
}


SDLInputHandler::~SDLInputHandler()
{
}
