#pragma once
#include <Engine.h>
#include <SDL_mixer.h>
#include <defines.h>
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void init();
	static void playSound(SOUND sound);
	void destroy();
	static Mix_Chunk* Alarm;



};
