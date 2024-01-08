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
	m_SCREEN_WIDTH = 1920;
	m_SCREEN_HEIGHT = 1080;

	SDL_Init(SDL_INIT_EVERYTHING);

	m_mainWindow = SDL_CreateWindow("SDL_Template",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, 0);

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

void Presenter::drawObject(Drawable& drawable, int angle) {

	SDL_RenderCopyEx(Presenter::m_mainRenderer, drawable.texture, nullptr, &drawable.rect, angle, nullptr, SDL_FLIP_NONE);

}

void Presenter::drawObject(SDL_Rect rect)
{
	SDL_RenderDrawRect(m_mainRenderer, &rect);
}

int Presenter::drawLine(int x1, int y1, int length, int angle)
{
	
	double angleRad = angle * M_PI / 180.0;

	
	int x2 = x1 + static_cast<int>(length * std::cos(angleRad));
	int y2 = y1 + static_cast<int>(length * std::sin(angleRad));

	SDL_RenderDrawLine(m_mainRenderer, x1, y1, x2, y2);

	return 0;
	
}

void Presenter::improveRenderer()
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	auto desktopWidth = DM.w;
	auto desktopHeight = DM.h;

	float2 mouseMultiply;
	float x = (double)m_SCREEN_WIDTH / (double)desktopWidth;
	float y = (double)m_SCREEN_HEIGHT / (double)desktopHeight;
	mouseMultiply.x = x;
	mouseMultiply.y = y;
	std::cout << mouseMultiply.x << " " << mouseMultiply.y;

	if (SDL_SetWindowFullscreen(m_mainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
	{
		cout << "SDL Renderer improve failed!" << SDL_GetError();
	}

	world.m_inputManager.setMouseMultiply(mouseMultiply);

	SDL_RenderSetLogicalSize(m_mainRenderer, m_SCREEN_WIDTH, m_SCREEN_HEIGHT);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

SDL_Texture* loadTexture(string path)
{
	return LoadTexture(path, Presenter::m_mainRenderer);
}

Drawable rotateTexture(Drawable texture)
{
	return Drawable();
}
