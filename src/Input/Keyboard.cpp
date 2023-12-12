#include "Input/Keyboard.h"
#include <algorithm>
#include "Util/Utility.h"



std::vector<Key>* Keyboard::_allKeys = new std::vector<Key>();
std::vector<pressedkey>* Keyboard::_pressedKeys = new std::vector<pressedkey>();
std::vector<pressedkey>* Keyboard::_keysUp = new std::vector<pressedkey>();
float Keyboard::_heldDelay = 0.1f;



//have an array of keys pressed
//update the pressed time
//if time is > time delay set key to key held
//if released remove the key from the pressed key array


/// <summary>
/// BIND ALL THE GLFW KEYS TO AN ARRAY OF KEYS
/// </summary>
void Keyboard::Init() {
	for (int i = 0; i < 65; i++) {
		char c = char(i + 32);
		if (i > 32 && i <= 58) {
			c = char(i + 64);
		}
		Key k(c);
		_allKeys->push_back(k);
	}
}




/// <summary>
/// THIS HAS A BUG WHERE THE KEY STAYS IN DOWN STATE for too long
/// 
/// </summary>
/// <param name="key"></param>
/// <param name="action"></param>
void Keyboard::HendleInput( unsigned int key, const unsigned int action) {
	key -= 32;
	//find the key			
	if (key >= 64 && key <= 90) {
		key -= 32;
	}
	if (action == 2 || key > _allKeys->size()) return;
	
	
	Key* k = &_allKeys->at(key);
	if (action == 1) {//IF KEY PRESSED
		k->state = KeyState::KEY_PRESS;
		_pressedKeys->push_back(pressedkey(false, k));
	}
	else {//IF KEY RELEASED
		k->state = KeyState::KEY_RELEASE;
		_keysUp->push_back(pressedkey(false, k));
		//REMOVE FROM PRESSED KEYS IF ITS THERE
		auto itt = _pressedKeys->begin();
		auto end = _pressedKeys->end();
		while (itt != end) {
			if ((*itt).second->key == k->key) {
				_pressedKeys->erase(itt);
				break;
			}
			itt++;
		}
	}
	

}





/// <summary>
/// update the pressed keys and check if it is time to set their states to keyheld
/// </summary>
/// <param name="deltaTime"></param>
void Keyboard::Update(float deltaTime) {

	//								HANDLE TRANSITION FROM KEY DOWN TO KEY HELD
	for (int i = 0; i < _pressedKeys->size();) {

		auto pKey = &_pressedKeys->at(i);

		if (pKey->first) {
			pKey->second->state = KeyState::KEY_DOWN;
			_pressedKeys->erase(_pressedKeys->begin() + i);
			i--;
		}
		else {
			pKey->first = true;
		}
		i++;

	}

	//								HANDLE TRANSITION FROM KEY HELD TO UP
	for (int i = 0; i < _keysUp->size();) {

		auto pKey = &_keysUp->at(i);

		if (pKey->first) {
			pKey->second->state = KeyState::IDLE;
			_keysUp->erase(_keysUp->begin() + i);
			i--;
		}
		else {
			pKey->first = true;
		}
		i++;
	}

}


const Key* Keyboard::GetKey(const char  key) {
	

	unsigned int  id = key - 32;
	if (id > 64 && id < 91) {
		id -= 32;
	}
	if (id < 0 || id >= _allKeys->size()) {
		printf("KEY NOT FOUND in get key  \n");
		return NULL;
	}
	
	return &_allKeys->at(id);
}


void Keyboard::Delete() {
	delete _allKeys;
	delete _pressedKeys;
	delete _keysUp;
	//delete _slPressed;
}