#include "Light.h"
#include <cmath>

Light::Light()
{
}

Light::~Light()
{
}

void Light::createLight(SDL_Rect cast_position, Uint8 r, Uint8 g, Uint8 b, Uint8 strength)
{
	SDL_SetRenderDrawBlendMode(Presenter::m_mainRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Presenter::m_mainRenderer, r, g, b, strength);
	SDL_RenderFillRect(Presenter::m_mainRenderer, &cast_position);


}

void Light::createShadows(SDL_Rect lightPosition, Drawable object)
{
    int distanceX = lightPosition.x - object.rect.x;

    
    int maxDistance = 100; 

    
    double alpha = 255.0 * (1.0 - std::min(1.0, static_cast<double>(distanceX) / maxDistance));

  
    Uint8 finalAlpha = std::max(0, std::min(255, static_cast<int>(alpha)));

    
    int shadowPositionX = object.rect.x + distanceX;

    SDL_SetRenderDrawBlendMode(Presenter::m_mainRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Presenter::m_mainRenderer, 0, 0, 0, finalAlpha);

    
    int shadowWidth = 20; 
    int shadowHeight = object.rect.h;

    SDL_Rect shadowRect = { object.rect.x, object.rect.y, shadowWidth, shadowHeight };
    SDL_RenderFillRect(Presenter::m_mainRenderer, &shadowRect);
}


