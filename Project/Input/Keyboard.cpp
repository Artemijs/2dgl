#include "Keyboard.h"
#include <algorithm>
std::vector<Key>* Keyboard::_allKeys = new std::vector<Key>();
std::vector<std::pair<float, Key>>* Keyboard::_pressedKeys = new std::vector<std::pair<float, Key>>();
float Keyboard::_heldDelay = 0.25f;
//have an array of keys pressed
//update the pressed time
//if time is > time delay set key to key held
//if released remove the key from the pressed key array
void Keyboard::Init() {
	for (int i = 0; i < 32; i++) {

		//_allKeys->push_back(Key{ const char(i + 97), KeyState::IDLE });
	}

}
void Keyboard::HendleInput(const unsigned int key, const unsigned int action) {
	//find the key								
	for (int i = 0; i < _allKeys->size(); i++) {
		Key* k = &_allKeys->at(i);				
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
	auto itt = _pressedKeys->begin();
	auto end = _pressedKeys->end();
	while ( itt != end) {
		std::pair<float, Key> k = (*itt);
		//check if the key has been hed long enough for it to count as key held
		(*itt).first += deltaTime;

		if ((*itt).first >= Keyboard::_heldDelay) {
			(*itt).second.state = KeyState::KEY_HELD;
			//_pressedKeys->erase(itt);
			//auto temp  = _pressedKeys->erase(itt);
			continue;
		}
		itt++;
	}

}
const Key* Keyboard::GetKey(const char  key) {
	for (int i = 0; i < _allKeys->size(); i++) {
		Key* k = &_allKeys->at(i);
		if (k->key == key) {
			return k;
		}
	}
	return NULL;
}
void Keyboard::Delete() {
	delete _allKeys;
	delete _pressedKeys;
}