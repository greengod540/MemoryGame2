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

bool colliding(SDL_Rect objectRect, SDL_Rect targetRect, int offsetx, int offsety) {
	bool checkCollisionX = false;
	bool checkCollisionY = false;


	if (objectRect.y + objectRect.h + offsety >= targetRect.y && objectRect.y <= targetRect.y + targetRect.h) {
		checkCollisionY = true;
	}


	if (objectRect.x + objectRect.w + offsetx >= targetRect.x && objectRect.x <= targetRect.x + targetRect.w) {
		checkCollisionX = true;
	}


	return checkCollisionX && checkCollisionY;
}