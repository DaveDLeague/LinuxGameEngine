#include "GameEngine/AudioPlayer.h"

AudioPlayer::AudioPlayer(){
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
		printf("SDL_Mixer ERROR: %s\n", SDL_GetError());
	}
}

AudioPlayer::~AudioPlayer(){
	for(std::map<std::string, Mix_Music*>::iterator it = musicTracks.begin(); it != musicTracks.end(); it++){
		Mix_FreeMusic(it->second);		
	}

	for(std::map<std::string, Mix_Chunk*>::iterator it = soundEffects.begin(); it != soundEffects.end(); it++){
		Mix_FreeChunk(it->second);		
	}
}

void AudioPlayer::loadSong(std::string songName, std::string songLoc){
	musicTracks[songName] = Mix_LoadMUS(songLoc.c_str());
	if(musicTracks[songName] == NULL){
		printf("SDL_Mixer ERROR loading song: %s\n", Mix_GetError());
	}
}

void AudioPlayer::loadSoundEffect(std::string effectName, std::string effectLoc){
	soundEffects[effectName] = Mix_LoadWAV(effectLoc.c_str());
	if(soundEffects[effectName] == NULL){
		printf("SDL_Mixer ERROR loading effect: %s\n", Mix_GetError());
	}
}

void AudioPlayer::playSong(std::string song){
	Mix_PlayMusic(musicTracks[song], -1);
}

void AudioPlayer::stopSong(std::string song){

}

void AudioPlayer::playSoundEffect(std::string effect){
	Mix_PlayChannel(-1, soundEffects[effect], 0);
}

void AudioPlayer::stopSoundEffect(std::string effect){
	
}
