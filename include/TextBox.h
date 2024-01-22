#pragma once
#include "Engine.h"
#include "TextCreator.h"
#include "Presenter.h"
#include <defines.h>




class TextBox {
public:
	Drawable txtbox;
	SDL_Texture* texture = loadTexture("Background.bmp");
	void createTextBox(SDL_Rect textRect, std::string text);
	
	
};