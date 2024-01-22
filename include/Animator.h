#include "Engine.h"
#include "defines.h"
#include <string>
#include "Presenter.h"
#include <memory>
#include <chrono>
#include <thread>
#pragma once

class Animator {
public:
	SDL_Texture* returnedTexture;
	int numFrames = 0;
	std::vector<SDL_Texture*> init(std::string imgPath, int frames, std::string imgName);
	SDL_Texture* returnFrame(std::vector<SDL_Texture*> animation, bool loop);
	SDL_Texture* texture;
	void resetFrame();
	bool animationFinished = false;
	
	
private:
	int currentFrame = 0;
	int currentIndex = 0;



};