#pragma once
#include <SDL.h>
#include "Presenter.h"
#include "defines.h"
#include "Engine.h"
class Light {

public:


	Light();
	~Light();


	void init();
	static void createLight(SDL_Rect lightPosition, Uint8 r, Uint8 g, Uint8 b, Uint8 strength);
	static void createShadows(SDL_Rect lightPosition, Drawable object);
	static std::vector<Drawable> findObjects(SDL_Rect lightPosition, std::vector<Drawable> objectVector);
	
	static Uint8 lightStrength;
	Drawable shadow;


	
	


};