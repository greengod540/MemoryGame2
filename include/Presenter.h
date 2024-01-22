#pragma once

#include "Engine.h"
#include "defines.h"

class Presenter
{
public:
	static SDL_Window* m_mainWindow;
	static SDL_Renderer* m_mainRenderer;

	static int m_SCREEN_WIDTH;
	static int m_SCREEN_HEIGHT;

	void init();
	void update();
	void draw();

	static void drawObject(SDL_Texture* texture);
	static void drawObject(Drawable& drawable);
	static void drawObject(DrawableSrcRect& drawableSrcRect);
	static void drawObject(Drawable& drawable, int angle, SDL_RendererFlip flip);
	static void drawObject(SDL_Rect rect);
	static int drawLine(int x1, int y1, int length, int angle);

	

private:
	void improveRenderer();
};

template <typename Params>
void drawObject(Params& value)
{
	Presenter::drawObject(value);
}

SDL_Texture* loadTexture(string path);
Drawable rotateTexture(Drawable texture);