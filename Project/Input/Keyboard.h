#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <vector>
enum class KeyState
{
	KEY_DOWN,
	KEY_HELD,
	KEY_UP,
	IDLE
};
struct Key {
public :
	const char key;
	KeyState state;
	Key(const char k) :key(k) { state = KeyState::IDLE; }
};
#include "../Util/Utility.h"
class Keyboard {
#define pressedkey std::pair<float, Key*>

private:
	static std::vector<Key>* _allKeys;
	static std::vector<pressedkey>* _pressedKeys;
	static std::vector<Key*>* _keysUp;
	static float _heldDelay;
	
public :
	static void Init();
	static void HendleInput( unsigned int key, const unsigned int action);
	static const Key* GetKey(const char key);
	void static Update(float deltaTime);
	static void Delete();

};
#endif