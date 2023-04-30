
#include "Button.h"
#include "../Game/MouseEventComponent.h"
Button::Button():BaseNode() {}
Button::Button(const Vec3 pos, const Vec3 size, const float ang) : BaseNode(pos, size, ang){
	MouseEvent<Button>* mouse_e = new MouseEvent<Button>(this);
	mouse_e->SetEventCallBack(&Button::OnPress, BtnEvent::ON_ENTER);
	AddComponent<MouseEvent<Button>>(mouse_e);
	Sprite* btton_bg = new Sprite();
	AddComponent<Sprite>(btton_bg);
}
void Button::OnPress() {
	printf("CALLING PRINFNT from BUTTON \n");
	printf("and does this have a destructor?\n");
}