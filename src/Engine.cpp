#include "Engine.h"


SDL_Texture* LoadTexture(string imgPath, SDL_Renderer* renderer)
{
	string tmpImg = IMG_FOLDER + imgPath;

	SDL_Surface* loadingSurface = SDL_LoadBMP(tmpImg.c_str());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
	SDL_Texture* shadowTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);

	if (texture == nullptr)
	{
		tmpImg = "img\\Null.bmp";

		loadingSurface = SDL_LoadBMP(tmpImg.c_str());

		texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
		shadowTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);

	}
	textures.push_back(shadowTexture);
	SDL_FreeSurface(loadingSurface);
	

	return texture;
}

bool isMouseInRect(int2 mouseCoor, SDL_Rect rect)
{
	if (mouseCoor.x >= rect.x && mouseCoor.x <= rect.x + rect.w && 
		mouseCoor.y >= rect.y && mouseCoor.y <= rect.y + rect.h)
	{
		return true;
	}

	return false;
}

bool collRectRect(SDL_Rect rect1, SDL_Rect rect2)
{
	if (rect1.x + rect1.w < rect2.x || rect1.x > rect2.x + rect2.w || rect1.y + rect1.h < rect2.y || rect1.y > rect2.y + rect2.h)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool colliding(SDL_Rect rect1, SDL_Rect rect2, int offsetx, int offsety) {
	bool checkCollisionX = false;
	bool checkCollisionY = false;


	if (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x && rect1.y < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y) {
		checkCollisionX = true;
		checkCollisionY = true;
	}

	return checkCollisionX && checkCollisionY;
}

bool isPointInsideEllipse(int x, int y, int ellipseCenterX, int ellipseCenterY, int ellipseWidth, int ellipseHeight)
{
	double normalizedX = static_cast<double>(x - ellipseCenterX) / (ellipseWidth / 2.0);
	double normalizedY = static_cast<double>(y - ellipseCenterY) / (ellipseHeight / 2.0);
	return (normalizedX * normalizedX + normalizedY * normalizedY) <= 1.0;
}
