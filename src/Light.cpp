#include "Light.h"
#include <cmath>
#include <Engine.h>

Light light;
Uint8 Light::lightStrength;

Light::Light() {
}

Light::~Light() {
}

void Light::init() {
    light.shadow.texture = loadTexture("shadow.bmp");
}

void Light::createLight(SDL_Rect cast_position, Uint8 r, Uint8 g, Uint8 b, Uint8 strength) {
    SDL_SetRenderDrawBlendMode(Presenter::m_mainRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Presenter::m_mainRenderer, r, g, b, strength);
    SDL_RenderFillRect(Presenter::m_mainRenderer, &cast_position);
    lightStrength = strength;
}

void Light::createShadows(SDL_Rect lightPosition, Drawable object) {
    int distanceX = lightPosition.x - object.rect.x;
    int distanceY = lightPosition.y - object.rect.y;

    int maxDistance = std::max(50, static_cast<int>(std::hypot(distanceX, distanceY)));

    double alpha = 255.0 * (1.0 - std::min(1.0, static_cast<double>(distanceX) / maxDistance));

    Uint8 finalAlpha = std::max(0, std::min(255, static_cast<int>(alpha)));

    SDL_SetRenderDrawBlendMode(Presenter::m_mainRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(Presenter::m_mainRenderer, 0, 0, 0, light.lightStrength);

    int shadowWidth = static_cast<int>(20 + (distanceX / 10.0));
    int shadowHeight = static_cast<int>(object.rect.h + (distanceY / 10.0));

    int shadowPositionX;
    int shadowPositionY;

    if (lightPosition.x >= Presenter::m_SCREEN_WIDTH / 2) {
        shadowPositionX = object.rect.x - 0.01 * (object.rect.w);
        shadowWidth++;
    }
    else {
        shadowPositionX = object.rect.x + object.rect.w - shadowWidth;
        shadowWidth--;
    }

    if (lightPosition.y >= Presenter::m_SCREEN_HEIGHT / 2) {
        shadowPositionY = object.rect.y - 0.01 * (object.rect.h);
        shadowHeight++;
    }
    else {
        shadowPositionY = object.rect.y + 0.01 * (object.rect.h);
        shadowHeight--;
    }

    // Smoothly rotate the shadows
    static double currentAngle = std::atan2(shadowPositionY, shadowPositionX) * (180.0 / M_PI);
    double targetAngle = std::atan2(lightPosition.y - object.rect.y, lightPosition.x - object.rect.x) * (180.0 / M_PI);
    double angle = currentAngle + 0.1 * (targetAngle - currentAngle); // ideqta za interpolato
    currentAngle = angle;

    light.shadow.rect = { shadowPositionX, shadowPositionY, shadowWidth, shadowHeight };

    Presenter::drawObject(light.shadow, angle);
}
