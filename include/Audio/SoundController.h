#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H
#include "SDL_mixer.h"
#include <vector>
class SoundCtrl {
private:
	static SoundCtrl* _instance;
	SoundCtrl();
	~SoundCtrl();
	std::vector<std::pair<const char*, Mix_Chunk*>>* _allSFX;
public:
	void CleanUp();
	const unsigned int LoadSFX(const char* path);
	const unsigned int LoadBGM(const char* path);
	void PlaySfx(int id);
	void PauseAudio();
	//sfxId the you get from calling LoadSFX and volume 0-255
	void SetSFXVolume(int sfxId, int volume);
	static SoundCtrl* GetInstance();


};

#endif