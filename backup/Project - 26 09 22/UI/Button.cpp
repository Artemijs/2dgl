#include "Button.h"
#include "../Graphics/Renderer.h"
#include "../Math/BoxBounds.h"
#include "../Audio/SoundController.h"
Button::Button() : Sprite("textures/btn.png", SpriteData()), 
MouseEvent(new BoxBounds(
	Vec3(-1, 1, 0),
	Vec3(1, 1, 0),
	Vec3(-1, -1, 0),
	Vec3(1, -1, 0))){


	_txt = new Text(Vec3(), 0, 6, "default");
	_shader = Renderer::instance()->GetShader(1);
	_texScale = Vec2(1, 0.25f);
	_uvOffset = Vec2(0, 3);

	_pressedSound = SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/btnPress.wav");
	_releasedSfx = SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/btnRelease.wav");
	_enterSfx = SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/enterBtn.wav");
	SoundCtrl::GetInstance()->SetSFXVolume(_enterSfx, 25);
}
Button::Button(const char* text, SpriteData rect): Sprite("textures/btn.png", rect),
MouseEvent(new BoxBounds(
	rect._position + Vec3(-rect._size.x * 0.5f, rect._size.y * 0.5f, 0),
	rect._position + Vec3(rect._size.x * 0.5f, rect._size.y * 0.5f, 0),
	rect._position + Vec3(-rect._size.x * 0.5f, -rect._size.y * 0.5f, 0),
	rect._position + Vec3(rect._size.x * 0.5f, -rect._size.y * 0.5f, 0) )) {

	Vec3 texPos = rect._position;
	texPos.z += 0.1f;
	_txt = new Text(texPos, 0.0f, 6, text);
	Text::GetDarkText(_txt);
	_shader = Renderer::instance()->GetShader(1);
	_texScale = Vec2(1, 0.25f);
	_uvOffset = Vec2(0, 3);
	_pressedSound = SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/btnPress.wav");
	_releasedSfx = SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/btnRelease.wav");
	_enterSfx = SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/enterBtn.wav");
	SoundCtrl::GetInstance()->SetSFXVolume(_enterSfx, 5);
}

Button::~Button() {
	delete _txt;
}
void Button::BeforeDraw() {
	Sprite::BeforeDraw();
	glUniform2f(glGetUniformLocation(_shader->ID, "uvOff"), _uvOffset.x, _uvOffset.y);
	glUniform2f(glGetUniformLocation(_shader->ID, "scale"), _texScale.x, _texScale.y);
}
void Button::Draw() {
	Sprite::Draw();
}
/*
void Button::UpdateMatrix(Matrix4x4 parent) {
	Matrix4x4 m = GetMatrix();
	m = m * parent;
	for (int i = 0; i < _all_children->size(); ++i) {
		_all_children->at(i)->UpdateMatrix(m);
	}
	SetMatrix(m);
}
Vec3 Button::GetPosition() {
	return position;
}
void Button::SetPosition(const Vec3* pos) {
	position = (*pos);
}*/
void Button::OnMouseEnter(const Vec2* mPos) {
	std::cout << "Mouse entered\n";
	_uvOffset = Vec2(0, 2);
	SoundCtrl::GetInstance()->PlaySfx(_enterSfx);
}
void Button::OnMouseLeave(const Vec2* mPos) {
	std::cout << "Mouse leave\n";
	_uvOffset = Vec2(0, 3);
}
void Button::OnClick(const Vec2* mPos) {
	std::cout << "Mouse click\n";
	
}
void Button::OnDoubleClick(const Vec2* mPos) {
	std::cout << "Mouse double click\n";
}
void Button::OnHover(const Vec2* mPos) {
	std::cout << "Mouse hover\n";
}
void Button::OnEndHover(const Vec2* mPos) {
	std::cout << "Mouse end hover\n";
}
void Button::OnPressed(const Vec2* mPos) {
	std::cout << "Pressed call\n";
	_uvOffset = Vec2(0, 1);
	SoundCtrl::GetInstance()->PlaySfx(_pressedSound);
}
void Button::OnReleased(const Vec2* mPos) {
	std::cout << "Released call\n";
	_uvOffset = Vec2(0, 2);
	SoundCtrl::GetInstance()->PlaySfx(_releasedSfx);
}