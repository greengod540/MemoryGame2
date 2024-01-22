#pragma once

#include "Engine.h"
#include<string>
#include "Player.h"
#include <Card.h>
#include <SDL.h>
#include <vector>
#include <map>
#include "Light.h"
#include "defines.h"
#include "Player.h"
#include "LevelCounter.h"



class Board
{
public:

	Board();
	~Board();

	
	void init();
	void draw();
	void destroy();
	void handleInput();
	int level = 1;


	SDL_Texture* m_background;
};