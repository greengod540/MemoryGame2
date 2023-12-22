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


private:
	static Mix_Chunk* m_backgroundMusic;
	static Mix_Chunk* m_playerColl;
	static Mix_Chunk* cardsSame;
	static Mix_Chunk* cardsNotSame;
	static Mix_Chunk* Success;
};
