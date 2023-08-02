#include "../Audio/SoundController.h"
#include "Button.h"
#include "../Game/MouseEventComponent.h"
#include "../Math/BoxBounds.h"
#include "Text.h"
Button::Button():
	BaseNode(),
	_pressedSfx(SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/btnPress.wav")),
	_releasedSfx(SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/btnRelease.wav")),
	_enterSfx(SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/enterBtn.wav")) {
	//set up mouse events
	MouseEvent* mouse_e = new MouseEvent();												
	Button* b = this;																	
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnPress(); }, BtnEvent::ON_PRESS);		
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnRelease(); }, BtnEvent::ON_RELEASE);	
	//mouse_e->AddEvent([&, b](const Vec3 v) {b->OnClick(); }, BtnEvent::ON_CLICK);				
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnDoublClick(); }, BtnEvent::ON_DOUBLE_CLICK);
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnEnter(); }, BtnEvent::ON_ENTER);
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnLeave(); }, BtnEvent::ON_LEAVE);
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnHover(); }, BtnEvent::ON_HOVER);
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnEndHover(); }, BtnEvent::ON_END_HOVER);
	AddComponent<MouseEvent>(mouse_e);	
	
	//init the material
	_material = new MaterialButton();	
	
	//add a back ground image
	Sprite* btton_bg = new Sprite(_material);
	AddComponent<Sprite>(btton_bg);		
	
	//add a collision box
	AddComponent<BoxBounds>(new BoxBounds(this));

	//create text
	BaseNode* bm = new BaseNode(Vec3(0, 0, 0.10f), Vec3(1, 1, 1), 0);
	bool bools[3] = { true, false, true };
	bm->SetInheritTransform(bools);		
	AddChild(bm);						
	bm->AddComponent<Text>(new Text("Button", bm, 15));

	//change btn sfx volume
	SoundCtrl::GetInstance()->SetSFXVolume(_enterSfx, 25);

}
Button::Button(const char * txt, const Vec3 pos, const Vec3 size, const float ang) : 
	BaseNode(pos, size, ang),
	_pressedSfx(SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/btnPress.wav")),
	_releasedSfx(SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/btnRelease.wav")),
	_enterSfx(SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/enterBtn.wav"))
{
	MouseEvent* mouse_e = new MouseEvent();
	//mouse_e->SetEventCallBack(&Button::OnPress, BtnEvent::ON_ENTER);
	Button* b = this;
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnPress(); }, BtnEvent::ON_PRESS);			
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnRelease(); }, BtnEvent::ON_RELEASE);		
	//mouse_e->AddEvent([&, b](const Vec3 v) {b->OnClick(); }, BtnEvent::ON_CLICK);			
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnDoublClick(); }, BtnEvent::ON_DOUBLE_CLICK);
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnEnter(); }, BtnEvent::ON_ENTER);			
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnLeave(); }, BtnEvent::ON_LEAVE);			
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnHover(); }, BtnEvent::ON_HOVER);			
	mouse_e->AddEvent([&, b](const Vec3 v) {b->OnEndHover(); }, BtnEvent::ON_END_HOVER);	
	AddComponent<MouseEvent>(mouse_e);	
	_material = new MaterialButton();	
	Sprite* btton_bg = new Sprite(_material);
	AddComponent<Sprite>(btton_bg);		
	AddComponent<BoxBounds>(new BoxBounds(this));
	BaseNode* bm = new BaseNode(Vec3(0, 0, 0.10f), Vec3(1,1,1), 0);
	bool bools[3] = { true, false, true};
	bm->SetInheritTransform(bools);		
	AddChild(bm);						
	bm->AddComponent<Text>(new Text(txt, bm, 15));
										
	SoundCtrl::GetInstance()->SetSFXVolume(_enterSfx, 25);
									
}
void Button::OnPress() {							
	//printf("CALLING OnPress \n");					
	_material->_uvOffset = Vec2(0, 1);
	SoundCtrl::GetInstance()->PlaySfx(_pressedSfx);
}													
void Button::OnRelease() {							
	//printf("CALLING OnRelease \n");	
	_material->_uvOffset = Vec2(0, 2);
	SoundCtrl::GetInstance()->PlaySfx(_releasedSfx);;
}													
void Button::OnClick() {
	//printf("CALLING OnClick \n");
	//printf("and does this have a destructor?\n");
}
void Button::OnDoublClick() {
	//printf("CALLING OnDoublClick \n");
	//printf("and does this have a destructor?\n");
}
void Button::OnEnter() {
	//printf("CALLING OnEnter \n");
	_material->_uvOffset = Vec2(0, 2);
	SoundCtrl::GetInstance()->PlaySfx(_enterSfx);
}
void Button::OnLeave() {
	//printf("CALLING OnLeave \n");
	_material->_uvOffset = Vec2(0, 3);
	//printf("and does this have a destructor?\n");
}
void Button::OnHover() {
	//printf("CALLING OnHover \n");
	//printf("and does this have a destructor?\n");
}
void Button::OnEndHover() {
	//printf("CALLING OnEndHover \n");
	//printf("and does this have a destructor?\n");
}