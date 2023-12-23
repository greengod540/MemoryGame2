#pragma once
#include <SDL_ttf.h>
#include "defines.h"
#include "Presenter.h"
#include <SDL.h>
class Text_Creator
{
public:
	static void TextCreate(const char* font, int size, int x, int y, int w, int h, const char* text, SDL_Color color);
	static Drawable text1;

};