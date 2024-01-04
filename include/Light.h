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
	static void createLight(SDL_Rect cast_position, Uint8 r, Uint8 g, Uint8 b, Uint8 strength);
	static void createShadows(SDL_Rect lightPosition, std::vector<Drawable> objectsVector, std::vector<SDL_Texture*> shadowTextures);
	static std::vector<Drawable> findObjects(SDL_Rect lightPosition, std::vector<Drawable> objectVector);
	
	SDL_Rect rayRect;
	static Uint8 lightStrength;
	Drawable shadow;
	void calculateShadow(const SDL_Rect& lightPosition, const SDL_Rect& rayRect, const Drawable& object, int& shadowPositionX, int& shadowPositionY, int& shadowWidth, int& shadowHeight, int& interpolatedAngle);





	
	


};