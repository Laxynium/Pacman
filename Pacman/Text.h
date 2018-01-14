#pragma once
#include "GameObject.h"
#include <memory>
#include "IRenderer.h"
#include <SDL_ttf.h>

class Text:public GameObject
{
	std::shared_ptr<IRenderer> _renderer;
	std::string _text;
	int _fontSize;
	bool _hasTextChanged = false;
	TTF_Font *_font = nullptr;
	Wrapper<SDL_Texture> _texture;
private://methods
	void SetTexture(const std::string& text);
public:
	Text(const std::shared_ptr<IRenderer>& renderer, const std::string& text = "",int fontSize=40);
	const std::string& GetText() const;
	void SetText(const std::string& text);
	void Draw() override;
	void Update() override;
};
