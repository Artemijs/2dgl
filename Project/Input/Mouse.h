#ifndef MOUSE_H
#define MOUSE_H
#include "../Math/Matrix4x4.h"


/*enum class MouseBtns{


};*/


class Mouse {
private:
	Vec2 _position;
	bool _hidden;

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
