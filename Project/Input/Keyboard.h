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
	const char key;
	KeyState state;
};
class Keyboard {
#define pressedkey std::pair<float, Key>
private:
	static std::vector<Key>* _allKeys;
	static std::vector<std::pair<float, Key>>* _pressedKeys;
	static float _heldDelay;
	
public :
	static void Init();
	static void HendleInput(const unsigned int key, const unsigned int action);
	static const Key* GetKey(const char key);
	void static Update(float deltaTime);
	static void Delete();

};
#endif