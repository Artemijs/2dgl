#ifndef BUTTON_H
#define BUTTON_H

#include "../Game/BaseNode.h"

class Button : public BaseNode {
private:

public :
	Button(const Vec3 pos, const Vec3 size, const float ang);
	Button();

	void OnPress();
};


#endif // !SPRITE_H
