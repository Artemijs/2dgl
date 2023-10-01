#include "Keyboard.h"
#include <algorithm>

#include "../Util/Utility.h"
std::vector<Key>* Keyboard::_allKeys = new std::vector<Key>();

std::vector<pressedkey>* Keyboard::_pressedKeys = new std::vector<pressedkey>();
std::vector<Key*>* Keyboard::_keysUp = new std::vector<Key*>();

float Keyboard::_heldDelay = 0.05f;



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
/// this can be optimised to index the key beased on key int value
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
	//IF KEY PRESSED
	if (action == 1) {
		k->state = KeyState::KEY_DOWN;
		//add new key to pressed keys
		pressedkey pk(0, k);
		_pressedKeys->push_back(pk);
	}
	else {
		//if KEY RELEASED
		k->state = KeyState::KEY_UP;
		_keysUp->push_back(k);
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

	while (_keysUp->size() != 0) {
		Key* k = _keysUp->at(0);
		k->state = KeyState::IDLE;
		_keysUp->erase(_keysUp->begin());
	}
	for (int i = 0; i < _pressedKeys->size();) {
		auto pKey = &_pressedKeys->at(i);
		pKey->first += deltaTime;
		printf("timer : %.3f state : %d\n", pKey->first, pKey->second->state);
		if (pKey->first >= Keyboard::_heldDelay) {
			pKey->second->state = KeyState::KEY_HELD;
			_pressedKeys->erase(_pressedKeys->begin() + i);
		}
		else {
			i++;
		}
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