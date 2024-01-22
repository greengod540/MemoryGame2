#include "Animator.h"
#include <memory>

std::vector<SDL_Texture*> Animator::init(std::string imgPath, int frames, std::string imgName)
{
    int numFrames;
    std::string currentString = "";
    std::vector<SDL_Texture*> textures;

    for (numFrames = 0; numFrames < frames; numFrames++) {
        currentString = imgPath + std::to_string(numFrames + 1) + imgName;
        textures.push_back(loadTexture(currentString));
    }

    return textures;
}

SDL_Texture* Animator::returnFrame(std::vector<SDL_Texture*> animation, bool loop)
{
    
    static Uint32 lastFrameTime = 0;
    const Uint32 frameDelay = 26;  // Adjust the frame delay (in milliseconds)

    if (animation.empty()) {
        // Handle the case where the animation vector is empty
        return nullptr; // Or some default texture
    }

    Uint32 currentTicks = SDL_GetTicks();

    if (currentTicks - lastFrameTime >= frameDelay) {
        // Enough time has passed, update the frame
        texture = animation[currentIndex];

        if (loop) {
            currentIndex = (currentIndex + 1) % animation.size();
        }
        if (loop && currentIndex == animation.size() - 1) {
            currentIndex = 0;
        }
        else if (!loop && currentIndex == animation.size() - 1) {
            currentIndex = 0;
        }

        lastFrameTime = currentTicks;
    }

    return texture;
}



void Animator::resetFrame()
{
    currentIndex = 0;
}


