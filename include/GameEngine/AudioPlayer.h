#pragma once

#include <string>
#include <map>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

struct AudioData
{
	Uint8* pos;
	Uint32 length;
};

class AudioPlayer{
public:
	AudioPlayer();
	virtual ~AudioPlayer();

	void loadSong(std::string songName, std::string songLoc);
	void loadSoundEffect(std::string effectName, std::string effectLoc);
	void playSong(std::string song);
	void stopSong(std::string song);
	void playSoundEffect(std::string effect);
	void stopSoundEffect(std::string effect);
private:

	std::map<std::string, Mix_Chunk*> soundEffects;
	std::map<std::string, Mix_Music*> musicTracks;
};
