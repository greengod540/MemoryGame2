#include "Engine.h"
#include "defines.h"

std::vector<Drawable> objects;


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

bool isPointInsideCircle(int x, int y, int centerX, int centerY, int radius)
{
	return ((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY)) <= (radius * radius);
}

Drawable createObject(Drawable object, SDL_Texture* objectTexture, SDL_Rect rect, bool shadowCast){


	object.texture = objectTexture;
	object.rect = rect;
	object.shadow_caster = shadowCast;
	objects.push_back(object);
	return object;

}

void objectDestroyer(Drawable object)
{
	SDL_DestroyTexture(object.texture);
	object.texture = nullptr;
	int indexToRemove = NULL;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].rect.x == object.rect.x && objects[i].rect.y == object.rect.y) {
			indexToRemove = i;
			break;
		}
	}
	if (indexToRemove != NULL) {
		objects.erase(objects.begin() + indexToRemove);
	}
	


}

void updateObject(Drawable object, bool shadowCast)
{
	int indexToRemove = NULL;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].rect.x == object.rect.x && objects[i].rect.y == object.rect.y) {
			indexToRemove = i;
			break;
		}
	}
	if (indexToRemove != NULL) {
		objects.erase(objects.begin() + indexToRemove);
	}
	createObject(object, object.texture, object.rect, shadowCast);



}

