#include "Text.h"
#include "Rect.h"

Text::Text(const std::shared_ptr<IRenderer>& renderer, const std::string& text,int fontSize): _renderer(renderer), _text(text)
{
	_font = TTF_OpenFont("assets/FFF_Tusj.ttf", fontSize);
	SetTexture(text);
}

const std::string& Text::GetText() const
{
	return _text;
}

void Text::SetText(const std::string& text)
{
	_text = text;
	_hasTextChanged = true;
	SetTexture(text);
}

void Text::Draw()
{
	auto pos = GetPosition();
	Rect dest{ pos.X(),pos.Y(),_width,_height };
	_renderer->CopyEx(_texture, &Rect{ 0,0,_width,_height }, &dest);
}

void Text::SetTexture(const std::string&text)
{
	const auto surface = TTF_RenderText_Solid(_font, text.c_str(), SDL_Color{ 255,255,255,0 });

	_texture = _renderer->CreateTextureFrom(Wrapper<SDL_Surface>([](SDL_Surface*s) {SDL_FreeSurface(s); }, surface));

	int w, h;
	SDL_QueryTexture(&_texture.Get(), nullptr, nullptr, &w, &h);
	_width = w, _height = h;
	
}

void Text::Update()
{
}
