#pragma once
#include <defines.h>
#include <iostream>
#include <fstream>
#include <Engine.h>
#include <defines.h>
#include <random>
class Card
{
public:
	Card();
	~Card();
	

	void init(std::string configFile);
	void reset();
	void destroy();
	void draw();
	void changeTextureBack();
	void changeTextureFront();
	void setRandomPos();
	int getCardID();
	void setCardID(int setID);
	void hide();
	void show();
	int ID;
	bool isVisible = true;
	Drawable card;
	SDL_Rect dstRect = { 0, 0, 0, 0 };
	int random = 0;
	SDL_Texture* front;
	SDL_Texture* back;
	SDL_Rect drawRect;
	bool selected = false;

private:







};

