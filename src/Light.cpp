#include "Light.h"
#include <cmath>
#include <Engine.h>
#include <iostream>
#include <algorithm>

#include <unordered_set>

Light light;
Uint8 Light::lightStrength;
int checkDuplicates = 0;

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

void Light::createShadows(SDL_Rect lightPosition, std::vector<Drawable> objectsVector, std::vector<SDL_Texture*> shadowTextures) {
    Drawable object;

    for (int i = 0; i < objectsVector.size(); i++) {
        object.rect = objectsVector[i].rect;
        light.shadow.texture = objectsVector[i].shadowTexture;
        
        SDL_SetTextureColorMod(light.shadow.texture, 0, 0, 0);
        

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


    
}



std::vector<Drawable> Light::findObjects(SDL_Rect lightPosition, const std::vector<Drawable> objectVector) {
    std::vector<Drawable> returnObjects;
    const double angleIncrement =  2 * M_PI / 21;  // Increase the precision
    int rayLength = 500;

    for (double angle = 0; angle < 2 * M_PI; angle += angleIncrement) {
        int endX = static_cast<int>(lightPosition.x + lightPosition.w / 2 + rayLength * std::cos(angle));
        int endY = static_cast<int>(lightPosition.y + lightPosition.h / 2 + rayLength * std::sin(angle));

        // Create SDL_Rect representing the ray
        SDL_Rect rayRect = { lightPosition.x + lightPosition.w / 2, lightPosition.y + lightPosition.h / 2, endX - lightPosition.x, endY - lightPosition.y };


        drawObject(rayRect);

        
        

        for (const auto& obj : objectVector) {
            if (SDL_HasIntersection(&rayRect, &obj.rect) || isPointInsideCircle(obj.rect.x, obj.rect.y, rayRect.x + rayRect.w / 2, rayRect.y + rayRect.h / 2, rayRect.w / 2)) {
                returnObjects.push_back(obj);
                checkDuplicates++;
             
            }
           
                
            
            if (checkDuplicates >= 2) {
                for (int i = 0; i < returnObjects.size(); ++i) {
                    for (int j = i + 1; j < returnObjects.size(); ++j) {
                        if (returnObjects[i].rect.x == returnObjects[j].rect.x || returnObjects[i].rect.y == returnObjects[j].rect.y) {
                            returnObjects.erase(returnObjects.begin() + i);
                        
                           
                              
                        }
                    }
                }
            }
        }
        
    }

    return returnObjects;
}




