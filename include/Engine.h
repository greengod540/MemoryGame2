#pragma once

#include "defines.h"

SDL_Texture* LoadTexture(string imgPath, SDL_Renderer* renderer);
bool isMouseInRect(int2 mouseCoor, SDL_Rect rect);
bool collRectRect(SDL_Rect rect1, SDL_Rect rect2);
bool colliding(SDL_Rect objectRect, SDL_Rect targetRect, int offsetx, int offsety);
static vector<SDL_Texture*> textures;
bool isPointInsideEllipse(int x, int y, int ellipseCenterX, int ellipseCenterY, int ellipseWidth, int ellipseHeight);
