#pragma once

#include "defines.h"
#include "objects.h"
#include <chrono>
#include <thread>

SDL_Texture* LoadTexture(string imgPath, SDL_Renderer* renderer);
bool isMouseInRect(int2 mouseCoor, SDL_Rect rect);
bool collRectRect(SDL_Rect rect1, SDL_Rect rect2);
bool colliding(SDL_Rect objectRect, SDL_Rect targetRect, int offsetx, int offsety);
bool collidingX(SDL_Rect rect1, SDL_Rect rect2, int offsetx);
bool collidingY(SDL_Rect rect1, SDL_Rect rect2, int offsety);
bool isPointInsideCircle(int x, int y, int centerX, int centerY, int radius);
Drawable createObject(Drawable object, SDL_Texture* objectTexture, SDL_Rect rect);
void objectDestroyer(Drawable object);
void updateObject(Drawable object, bool shadowCast);
static bool Timer(int durationInSeconds)
{
	static auto start = std::chrono::steady_clock::now();
	static auto end = start + std::chrono::seconds(durationInSeconds);

	if (std::chrono::steady_clock::now() < end) {
		std::cout << "Not passed time\n"; // Timer not expired
		return true;
	}
	else {
		return false;
	}

	// Update the end time for the next use
	end = std::chrono::steady_clock::now() + std::chrono::seconds(durationInSeconds);

	std::cout << "Timer expired\n";

}