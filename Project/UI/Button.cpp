
#include "Button.h"
#include "../Game/MouseEventComponent.h"
#include "../Math/BoxBounds.h"
Button::Button():BaseNode() {}
Button::Button(const Vec3 pos, const Vec3 size, const float ang) : BaseNode(pos, size, ang){
	MouseEvent* mouse_e = new MouseEvent();
	//mouse_e->SetEventCallBack(&Button::OnPress, BtnEvent::ON_ENTER);
	Button* b = this;
	//mouse_e->AddEvent([&, b](const Vec3 v) {b->OnPress(); }, BtnEvent::ON_PRESS);			
	//mouse_e->AddEvent([&, b](const Vec3 v) {b->OnRelease(); }, BtnEvent::ON_RELEASE);		
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnClick(); }, BtnEvent::ON_CLICK);			
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnDoublClick(); }, BtnEvent::ON_DOUBLE_CLICK);
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnEnter(); }, BtnEvent::ON_ENTER);			
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnLeave(); }, BtnEvent::ON_LEAVE);			
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnHover(); }, BtnEvent::ON_HOVER);			
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnEndHover(); }, BtnEvent::ON_END_HOVER);	
	AddComponent<MouseEvent>(mouse_e);	
	Sprite* btton_bg = new Sprite();	
	AddComponent<Sprite>(btton_bg);		
	AddComponent<BoxBounds>(new BoxBounds());
}
void Button::OnPress() {							
	printf("CALLING OnPress \n");					
	//printf("and does this have a destructor?\n");	
}													
void Button::OnRelease() {							
	printf("CALLING OnRelease \n");					
	//printf("and does this have a destructor?\n");	
}													
void Button::OnClick() {
	printf("CALLING OnClick \n");
	//printf("and does this have a destructor?\n");
}
void Button::OnDoublClick() {
	printf("CALLING OnDoublClick \n");
	//printf("and does this have a destructor?\n");
}
void Button::OnEnter() {
	printf("CALLING OnEnter \n");
	//printf("and does this have a destructor?\n");
}
void Button::OnLeave() {
	printf("CALLING OnLeave \n");
	//printf("and does this have a destructor?\n");
}
void Button::OnHover() {
	printf("CALLING OnHover \n");
	//printf("and does this have a destructor?\n");
}
void Button::OnEndHover() {
	printf("CALLING OnEndHover \n");
	//printf("and does this have a destructor?\n");
}