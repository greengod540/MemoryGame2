#include "SoundManager.h"
#include <iostream>
#include <SDL_mixer.h>
#include <defines.h>

Mix_Chunk* SoundManager::Alarm = nullptr;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::init()
{

	std::fstream stream;
	std::string tmp, ALarm;

	stream.open("config\\soundManager.txt");
	stream >> tmp >> ALarm;
	stream.close();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) {
		std::cout << Mix_GetError();

	}
	Alarm = Mix_LoadWAV((SOUND_FOLDER + ALarm).c_str());

	


}

void SoundManager::playSound(SOUND sound)
{
	Mix_AllocateChannels(2);




	switch (sound) {
	case ALARM:
		if (Alarm == nullptr) {
			std::cerr << "Error loading sound: " << Mix_GetError() << std::endl;
			// Handle the error (e.g., throw an exception or exit the program)
		}
		else {
			std::cout << "geqgeqf" << endl;
			Mix_PlayChannel(1, Alarm, 0);
			Mix_Volume(1, 30);
		}
		break;
	
		


	}




}

void SoundManager::destroy()
{
	Mix_FreeChunk(Alarm);

}
