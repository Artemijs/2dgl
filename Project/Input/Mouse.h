#ifndef MOUSE_H
#define MOUSE_H
#include "../Math/Matrix4x4.h"



enum class MouseKeyState{

	KEY_DOWN,
	KEY_HELD,
	KEY_UP,
	IDLE

};


struct MouseKey {
	const unsigned int _id;
	MouseKeyState _state;
};


/// <summary>
/// GLFW only allows for 8 mouse buttons
/// </summary>
class Mouse {

private:

	Vec2 _position;
	bool _hidden;
	//all keys

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

};

#endif // !MOUSE_H
