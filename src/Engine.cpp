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
	SDL_Point mousePosiiton = {mouseCoor.x, mouseCoor.y};
	if (SDL_PointInRect(&mousePosiiton, &rect)) {
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

bool collidingX(SDL_Rect rect1, SDL_Rect rect2, int offsetx)
{
	bool checkCollisionX = false;
	if (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x) {
		checkCollisionX = true;
		
	}
	return checkCollisionX;
}

bool collidingY(SDL_Rect rect1, SDL_Rect rect2, int offsety)
{
	bool checkCollisionY = false;
	if (rect1.y < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y) {
		checkCollisionY = true;
	}
	return checkCollisionY;
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

bool Timer(int durationInSeconds)
{
	auto duration = std::chrono::seconds(durationInSeconds);

	// Get the current time point
	auto start = std::chrono::steady_clock::now();

	// Calculate the end time point
	auto end = start + duration;

	// Main loop
	while (std::chrono::steady_clock::now() < end) {
		// Your code here

		// Sleeping for a short duration to avoid high CPU usage
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << "Timer expired!\n";

	// Return true indicating that the timer has expired
	return true;
}

