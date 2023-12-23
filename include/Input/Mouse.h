#ifndef MOUSE_H
#define MOUSE_H
#include "Math/Matrix4x4.h"
#include <vector>
#include <utility>///for pair
#include <functional>
#include "Util/Utility.h"

enum class MouseKeyState{

	KEY_PRESS,
	KEY_DOWN,
	KEY_RELEASE,
	IDLE

};


struct MouseKey {
	const unsigned int _id;
	MouseKeyState _state;
};

#define mkeyPress std::pair<bool, MouseKey*>
#define mouse_call std::function<bool(const Vec2& mousePos)>






/// <summary>
/// GLFW only allows for 8 mouse buttons
/// </summary>
class Mouse {

private:

	Vec2 _position;
	bool _hidden;
	std::vector<MouseKey> * _allKeys;
	std::vector<mkeyPress>* _keysPressed;
	std::vector<mkeyPress>* _keysUp;
	//key id, lambuda duraivu
	SList<std::pair<const unsigned int, mouse_call>*>* _mDownCalls;
	const unsigned int _maxKeys;
	//					all keys
	//std::vector<std::pair<const unsigned int, mouse_call>>* _mDownCalls;
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="type">0 : mDown, 1: mUp</param>
	/// <param name="mk"></param>
	void CallCalls(const unsigned int type, const MouseKey* mk);

public :

	Mouse();
	~Mouse();

	void Update(const float deltaTime);
	void ButtonInput(const unsigned int btn, const unsigned int action);
	void SetCursorPos(const float &x, const float &y);
	void SetCursorPos(const Vec2& cursorpos);
	Vec2 GetPosition();
	/// <summary>
	/// hides the cursor
	/// </summary>
	/// <param name="hidden"></param>
	void SetCursorHidden(const bool hidden);
	bool IsHidden();
	MouseKey* GetMouseKey(const unsigned int key);
	Vec3 GetMousePosV3();
	/// <summary>
	/// set callbacks for mouse button press events
	/// </summary>
	/// <param name="type">0 : mDown, 1: mUp</param>
	/// <param name="call">pass by copy pair of int(mouse btn) and LAMBUDDA DURAIVU void(const Vec2& mousePos)</param>
	void AddCallback(const unsigned int type, std::pair<const unsigned int, mouse_call>* call);
};

#endif // !MOUSE_H
