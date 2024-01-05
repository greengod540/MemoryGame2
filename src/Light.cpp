#include <Light.h>
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

void Light::rayTrace(SDL_Rect lightPosition, std::vector<Drawable> objectsVector) { //napravih ray trace prostotiq sushto
    const int rayLength = 700;
    const double angleIncrement = M_PI / 180.0;

    for (int i = 0; i <= 45; i++) {
        double angleRad = i * M_PI / 180.0;

        int x1 = lightPosition.x;
        int y1 = lightPosition.y;
        //Presenter::drawLine(lightPosition.x, lightPosition.y, rayLength, i);
        for (int length = 0; length <= rayLength; length++) {
            int x2 = x1 + static_cast<int>(length * std::cos(angleRad));
            int y2 = y1 + static_cast<int>(length * std::sin(angleRad));
            int shadowX = x2;
            int shadowY = y2;
            SDL_Rect rayRect = { x2, y2, 1, 1 };

            bool collided = false;

            for (int z = 0; z < objectsVector.size(); z++) {
                if (SDL_HasIntersection(&rayRect, &objectsVector[z].rect)) {
                    SDL_SetRenderDrawColor(Presenter::m_mainRenderer, 0, 0, 0, 255);
                    shadowX = x2 + static_cast<int>(length * std::cos(angleRad));
                    shadowY = y2 + static_cast<int>(length * std::sin(angleRad));

                    Presenter::drawLine(shadowX, shadowY, 700, i);
                    SDL_SetRenderDrawColor(Presenter::m_mainRenderer, 0, 0, 255, 255); 
                    SDL_Rect shadowRect = { shadowX, shadowY, 50, 50 };
                    SDL_RenderFillRect(Presenter::m_mainRenderer, &shadowRect);
                    collided = true;
                    break;
                }
            }

            if (collided) {
                break; // tuka breakvame out of loop
            }

        }

    }

}

void Light::createShadows(SDL_Rect lightPosition, std::vector<Drawable> objectsVector, std::vector<SDL_Texture*> shadowTextures) { // tova ne znam kak se poluchi
    Drawable object;

    for (int i = 0; i < objectsVector.size(); i++) {
        object.rect = objectsVector[i].rect;
        light.shadow.texture = objectsVector[i].shadowTexture;

        SDL_SetTextureColorMod(light.shadow.texture, 0, 0, 0);

        int shadowPositionX, shadowPositionY, shadowWidth, shadowHeight, interpolatedAngle;
        light.calculateShadow(lightPosition, light.rayRect, object, shadowPositionX, shadowPositionY, shadowWidth, shadowHeight, interpolatedAngle);

        light.shadow.rect = { shadowPositionX, shadowPositionY, shadowWidth, shadowHeight };



        Presenter::drawObject(light.shadow, interpolatedAngle);
    }
}





std::vector<Drawable> Light::findObjects(SDL_Rect lightPosition, const std::vector<Drawable> objectVector) { // gospodi pomilvai
    std::vector<Drawable> returnObjects;
    const double angleIncrement = 2 * M_PI / 360;  // Increase the precision
    int rayLength = 500;

    for (double angle = 0; angle < 2 * M_PI; angle += angleIncrement) {
        int endX = static_cast<int>(lightPosition.x + lightPosition.w / 2 + rayLength * std::cos(angle));
        int endY = static_cast<int>(lightPosition.y + lightPosition.h / 2 + rayLength * std::sin(angle));

        
        SDL_Rect rayRect = { lightPosition.x + lightPosition.w / 2, lightPosition.y + lightPosition.h / 2, endX - lightPosition.x, endY - lightPosition.y };







        for (const auto& obj : objectVector) {
            if (SDL_HasIntersection(&rayRect, &obj.rect) || isPointInsideCircle(obj.rect.x, obj.rect.y, rayRect.x + rayRect.w / 2, rayRect.y + rayRect.h / 2, rayRect.w / 2)) {
                returnObjects.push_back(obj);
                checkDuplicates++;

            }



            if (checkDuplicates >= 2) {
                for (int i = 0; i < returnObjects.size(); ++i) {
                    for (int j = i + 1; j < returnObjects.size(); ++j) {
                        if (returnObjects[i].rect.x == returnObjects[j].rect.x || returnObjects[i].rect.y == returnObjects[j].rect.y) {
                            returnObjects.erase(returnObjects.begin() + j);



                        }
                    }
                }
            }
        }

    }

    return returnObjects;
}

void Light::calculateShadow(const SDL_Rect& lightPosition, const SDL_Rect& rayRect, const Drawable& object, int& shadowPositionX, int& shadowPositionY, int& shadowWidth, int& shadowHeight, int& interpolatedAngle) {
    int distanceX = lightPosition.x - object.rect.x; //chatgpt e nai velikiq matematik
    int distanceY = lightPosition.y - object.rect.y;

    int maxDistance = std::max(50, static_cast<int>(std::hypot(distanceX, distanceY)));

    double angle = std::atan2(object.rect.y + object.rect.h / 2 - lightPosition.y, object.rect.x + object.rect.w / 2 - lightPosition.x);

    shadowWidth = static_cast<int>(20 + (std::abs(distanceX) / 10.0));
    shadowHeight = static_cast<int>(object.rect.h + (std::abs(distanceY) / 10.0));

    shadowPositionX = (lightPosition.x >= object.rect.x / 2) ?
        (object.rect.x - 0.01 * (object.rect.w)) :
        (object.rect.x + object.rect.w - shadowWidth);

    shadowPositionY = (lightPosition.y >= object.rect.y / 2) ?
        (object.rect.y - 0.01 * (object.rect.h)) :
        (object.rect.y + object.rect.h - shadowHeight);


    shadowWidth = std::max(1, shadowWidth);
    shadowHeight = std::max(1, shadowHeight);

    double currentAngle = std::atan2(shadowPositionY + shadowHeight / 2 - lightPosition.y, shadowPositionX + shadowWidth / 2 - lightPosition.x) * (180.0 / M_PI);
    double targetAngle = angle * (180.0 / M_PI);
    interpolatedAngle = currentAngle + 0.1 * (targetAngle - currentAngle);


    currentAngle = interpolatedAngle;


    shadowPositionX += rayRect.x;
    shadowPositionY += rayRect.y;
}