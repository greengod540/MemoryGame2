#pragma once
#include <SDL.h>
#include "Presenter.h"
class Light {

public:


	Light();
	~Light();


	static void createLight(SDL_Rect cast_position, Uint8 r, Uint8 g, Uint8 b, Uint8 strength);
	static void createShadows(SDL_Rect lightPosition, Drawable object);
	


};