#ifndef BUTTON_H
#define BUTTON_H

#include "../Game/BaseNode.h"
#include "../Graphics/Materials/MaterialButton.h"
class Button : public BaseNode {
private:
	 MaterialButton* _material;
	 const unsigned int _pressedSfx;
	 const unsigned int _releasedSfx;
	 const unsigned int _enterSfx;
public :
	Button(const char* txt, const Vec3 pos, const Vec3 size, const float ang);
	Button();
	/*
	ON_PRESS = 0,
	ON_RELEASE,
	ON_CLICK,
	ON_DOUBLE_CLICK,
	ON_ENTER,
	ON_LEAVE,
	ON_HOVER,
	ON_END_HOVER,
	*/
	void OnPress();
	void OnRelease();
	void OnClick();
	void OnDoublClick();
	void OnEnter();
	void OnLeave();
	void OnHover();
	void OnEndHover();
	
};


#endif // !SPRITE_H
