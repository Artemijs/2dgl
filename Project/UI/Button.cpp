
#include "Button.h"
#include "../Game/MouseEventComponent.h"
#include "../Math/BoxBounds.h"
Button::Button():BaseNode() {}
Button::Button(const Vec3 pos, const Vec3 size, const float ang) : BaseNode(pos, size, ang){
	MouseEvent* mouse_e = new MouseEvent();
	//mouse_e->SetEventCallBack(&Button::OnPress, BtnEvent::ON_ENTER);
	Button* b = this;
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnPress(); }, BtnEvent::ON_ENTER);
	AddComponent<MouseEvent>(mouse_e);
	Sprite* btton_bg = new Sprite();
	AddComponent<Sprite>(btton_bg);
	AddComponent<BoxBounds>(new BoxBounds());
}
void Button::OnPress() {
	printf("CALLING PRINFNT from BUTTON \n");
	printf("and does this have a destructor?\n");
}