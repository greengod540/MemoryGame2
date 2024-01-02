#pragma once

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <random>

using namespace std;

static string IMG_FOLDER = "img\\";
static string CONFIG_FOLDER = "config\\";
static string SOUND_FOLDER = "sound\\";
static string CARD_FOLDER = "card\\";
static string FONT_FOLDER = "font\\";

struct int2
{
	int x;
	int y;

	void reset()
	{
		x = 0;
		y = 0;
	}

	void set(int2 b) 
	{
		x = b.x;
		y = b.y;
	}

	void operator*=(int2 a)
	{
		x *= a.x;
		y *= a.y;
	}

	void operator/=(int2 a)
	{
		x /= a.x;
		y /= a.y;
	}

	int2 operator*(int2 a)
	{
		x *= a.x;
		y *= a.y;

		return *this; //Returns instance of the current class (After the modifications)
	}

	int2 operator/(int2 a)
	{
		x /= a.x;
		y /= a.y;

		return *this;
	}

	bool operator!=(int2 a)
	{
		if (x == a.x && y == a.y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool operator==(int2 a)
	{
		if (x == a.x && y == a.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct Drawable 
{
	SDL_Texture* texture;
	SDL_Rect rect; //dstRect;
	bool shadow_caster;
};

static vector<Drawable> objects;


struct DrawableSrcRect : Drawable
{
	SDL_Rect srcRect;
};

enum SOUND
{

	BACKGROUND_MUSIC,
	PLAYER_COLLISION,
	CARDS_SAME,
	CARDS_NOT_SAME,
	SUCCESS,
	QUIT,
	BACKGROUND2


};