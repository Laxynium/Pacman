#include "SDLRenderer.h"
#include<SDL_image.h>


SDLRenderer::SDLRenderer():
	_window(SDL_CreateWindow("PACMAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		896, 1030/*992*/, SDL_WindowFlags::SDL_WINDOW_SHOWN),
	[](SDL_Window*win)
	{
		SDL_DestroyWindow(win);
	}),
	_renderer(SDL_CreateRenderer(_window.get(), -1, 0),
	[](SDL_Renderer*ren)
	{
		SDL_DestroyRenderer(ren);
	})
{
}

void SDLRenderer::SetRenderDrawColor(Color color)
{
	SDL_SetRenderDrawColor(_renderer.get(),color.r,color.g,color.b,color.a);
}

Wrapper<SDL_Texture> SDLRenderer::CreateTextureFrom(Wrapper<SDL_Surface>& surface)
{
	return Wrapper<SDL_Texture>([](SDL_Texture*t) {SDL_DestroyTexture(t); }, SDL_CreateTextureFromSurface(_renderer.get(), &surface.Get()));
}

void SDLRenderer::Clear()
{
	SDL_RenderClear(_renderer.get());
}

void SDLRenderer::DrawRect(Rect rect)
{
	auto sdl_rect = SDL_Rect{ rect.x,rect.y,rect.w,rect.h };
	const auto color = rect.color;
	SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(_renderer.get(), &sdl_rect);
}

void SDLRenderer::FillRect(Rect rect)
{
	auto sdl_rect = SDL_Rect{ rect.x,rect.y,rect.w,rect.h };
	const auto color = rect.color;
	SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(_renderer.get(), &sdl_rect);
}

void SDLRenderer::CopyEx(Wrapper<SDL_Texture>& texture, Rect* source, Rect* destination, double angle)
{
	SDL_Rect *srect=nullptr;
	SDL_Rect *drect=nullptr;
	if (source != nullptr)
		srect = &SDL_Rect{ source->x,source->y,source->w,source->h };
	if(destination!=nullptr)
		drect= &SDL_Rect{ destination->x,destination->y,destination->w,destination->h };
	
	//SDL_RenderCopy(_renderer.get(),&texture.Get(),srect, drect);
	SDL_RenderCopyEx(_renderer.get(), &texture.Get(), srect, drect, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);

}

void SDLRenderer::Present()
{
	SDL_RenderPresent(_renderer.get());
}
