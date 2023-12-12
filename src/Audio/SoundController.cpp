#include "Audio/SoundController.h"
#include <iostream>
SoundCtrl* SoundCtrl::_instance = NULL;

SoundCtrl* SoundCtrl::GetInstance() {
	if (_instance == NULL) {
		_instance = new SoundCtrl();
	}
	return _instance;
}
SoundCtrl::SoundCtrl() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		//printf("audio error %s\n", Mix_GetError());
		std::cout << "Audio error " << Mix_GetError() << "\n";
	}
	Mix_Volume(-1, 75);
	_allSFX = new std::vector<std::pair<const char*, Mix_Chunk*>>();
}
SoundCtrl::~SoundCtrl() {

}
void SoundCtrl::CleanUp() {

	for (int i = 0; i < _allSFX->size(); i++) {
		Mix_FreeChunk(_allSFX->at(i).second);
		_allSFX->at(i).second = NULL;
	}
	delete _allSFX;
	Mix_CloseAudio();
}
const unsigned int SoundCtrl::LoadSFX(const char* path) {
	//check if exissts
	bool found = false;
	for (int i = 0; i < _allSFX->size(); ++i) {
		const char* p = _allSFX->at(i).first;
		for (int j = 0; p[j] == path[j]; j++) {
			//if the strings are of different sizes
			/*if (p[j] == '\0' || path[j] == '\0') {
				break;
			}*/
			//if strings are identical
			if (p[j] == '\0' && path[j] == '\0') {
				//dont need to add it because it already exists
				found = true;
				return i;
				break;
			}
		}
	}
	if (!found)
		//add new if not exists
		_allSFX->push_back(
			std::pair<const char*, Mix_Chunk*>{path, Mix_LoadWAV(path)});
	return _allSFX->size() - 1;
}
const unsigned int SoundCtrl::LoadBGM(const char* path) {
	return 0;
}
void SoundCtrl::PlaySfx(int id) {
	Mix_PlayChannel(-1, _allSFX->at(id).second, 0);
}
void SoundCtrl::PauseAudio() {

}
void SoundCtrl::SetSFXVolume(int sfxId, int volume) {
	Mix_VolumeChunk(this->_allSFX->at(sfxId).second, volume);
}