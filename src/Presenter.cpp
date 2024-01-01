#include "Presenter.h"
#include "World.h"
#include "defines.h"

extern World world;

SDL_Window* Presenter::m_mainWindow = nullptr;
SDL_Renderer* Presenter::m_mainRenderer = nullptr;
int Presenter::m_SCREEN_WIDTH = 0;
int Presenter::m_SCREEN_HEIGHT = 0;

void Presenter::init()
{
	

	SDL_Init(SDL_INIT_EVERYTHING);
	
	m_mainWindow = SDL_CreateWindow("SDL_Template",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, 0);

	

	m_mainRenderer = SDL_CreateRenderer(m_mainWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	improveRenderer();
}

void Presenter::update()
{

}

void Presenter::draw()
{

	SDL_RenderPresent(m_mainRenderer);
	
	SDL_RenderClear(m_mainRenderer);

	
	

}

void Presenter::drawObject(SDL_Texture* texture)
{
	SDL_SetRenderDrawBlendMode(m_mainRenderer, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(m_mainRenderer, texture, NULL, NULL);
}

void Presenter::drawObject(Drawable& drawable)
{
	SDL_SetRenderDrawBlendMode(m_mainRenderer, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(m_mainRenderer, drawable.texture, NULL, &drawable.rect);
}

void Presenter::drawObject(DrawableSrcRect& drawableSrcRect)
{
	SDL_SetRenderDrawBlendMode(m_mainRenderer, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(m_mainRenderer, drawableSrcRect.texture, &drawableSrcRect.rect, &drawableSrcRect.srcRect);
}

void Presenter::improveRenderer()
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	auto desktopWidth = DM.w;
	auto desktopHeight = DM.h;
	m_SCREEN_HEIGHT = DM.h;
	m_SCREEN_WIDTH = DM.w;

	int2 mouseMultiply;

	mouseMultiply.x = m_SCREEN_WIDTH / desktopWidth;
	mouseMultiply.y = m_SCREEN_HEIGHT / desktopHeight;

	world.m_inputManager.setMouseMultiply(mouseMultiply);

	if (SDL_SetWindowFullscreen(m_mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
	{
		cout << "SDL Renderer improve failed!" << SDL_GetError();
	}

	SDL_RenderSetLogicalSize(m_mainRenderer, m_SCREEN_WIDTH, m_SCREEN_HEIGHT);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

}

SDL_Texture* loadTexture(string path)
{
	return LoadTexture(path, Presenter::m_mainRenderer);
}
