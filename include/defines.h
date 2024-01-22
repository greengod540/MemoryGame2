#pragma once

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <random>
#include <vector>
#include <functional>
using namespace std;

static string IMG_FOLDER = "img\\";
static string PLAYER_FOLDER = "player\\";
static string CONFIG_FOLDER = "config\\";
static string SOUND_FOLDER = "sound\\";
static string FONT_FOLDER = "font\\";
static string DIALOGUE_FOLDER = "Dialogue\\";
static string BACKGROUND_FOLDER = "Backgrounds\\";
static bool dialogue_engaged = false;
static std::vector<std::function<void()>> levels;
static bool isLevelFinished = false;
static string INTERIOR_FOLDER = "Interiors\\";
static int tech = 2;							
static int Speech = 5;
static int Strength = 2;
static int Sneak = 2;
static bool isRobotTriggered = false;

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

struct float2
{
	float x;
	float y;

	void reset()
	{
		x = 0;
		y = 0;
	}

	void set(float2 b)
	{
		x = b.x;
		y = b.y;
	}

	void operator*=(float2 a)
	{
		x *= a.x;
		y *= a.y;
	}

	void operator/=(float2 a)
	{
		x /= a.x;
		y /= a.y;
	}

	float2 operator*(float2 a)
	{
		x *= a.x;
		y *= a.y;

		return *this; //Returns instance of the current class (After the modifications)
	}

	float2 operator/(float2 a)
	{
		x /= a.x;
		y /= a.y;

		return *this;
	}

	bool operator!=(float2 a)
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

	bool operator==(float2 a)
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
	SDL_Texture* shadowTexture;
};

struct Animation
{
	Drawable object;
	std::vector<SDL_Texture*> animation;
};




struct DrawableSrcRect : Drawable
{
	SDL_Rect srcRect;
};

enum SOUND
{
	ALARM


};