#include "Keyboard.h"
#include <algorithm>
std::vector<Key*>* Keyboard::_allKeys = new std::vector<Key*>();
std::vector<pressedkey>* Keyboard::_pressedKeys = new std::vector<pressedkey>();
//have an array of keys pressed
//update the pressed time
//if time is > time delay set key to key held
//if released remove the key from the pressed key array
void Keyboard::Init() {
	
}
void Keyboard::HendleInput(const unsigned int key, const unsigned int action) {
	//find the key
	for (int i = 0; i < _allKeys->size(); i++) {

		Key* k = _allKeys->at(i);
		if (k->key == key) {
			if (k->state == KeyState::IDLE) {
				k->state = KeyState::KEY_DOWN;
			}
			else if (k->state == KeyState::KEY_DOWN){
				k->state = KeyState::KEY_DOWN;
			}	
		}
	}
}
void Keyboard::Update(float deltaTime) {
	for (int i = 0; i < _pressedKeys->size(); ++i) {
		pressedkey k = _pressedKeys->at(i);
		//check if the key has been hed long enough for it to count as key held
		k.first += deltaTime;
		if (k.first >= Keyboard::_heldDelay) {
			k.second->state = KeyState::KEY_HELD;
			//remove the key from the array
			//_pressedKeys->erase(
			//i--;
			
		}
	}
}
const Key* Keyboard::GetKey(const char  key) {
	for (int i = 0; i < _allKeys->size(); i++) {
		Key* k = _allKeys->at(i);
		if (k->key == key) {
			return k;
		}
	}
	return NULL;
}
void Keyboard::Delete() {
	for (int i = 0; i < _allKeys->size(); i++) {
		delete _allKeys->at(i);
	}
	delete _allKeys;
	delete _pressedKeys;
}