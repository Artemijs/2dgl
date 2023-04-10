#include "Button.h"
#include "../Graphics/Renderer.h"
#include "../Math/BoxBounds.h"
#include "../Audio/SoundController.h"
#include "../Game/Game.h"
namespace v1_5 {
	Button::Button() : Sprite("Assets/Textures/btn.png", Vec3(0, 0, 0), Vec3(50, 50, 1), 0, Game::_world),
		MouseEvent(new BoxBounds(
			Vec3(-1, 1, 0),
			Vec3(1, 1, 0),
			Vec3(-1, -1, 0),
			Vec3(1, -1, 0)), this) {


		_txt = new Text(Vec3(), 0, 6, "default");
		AddChild(_txt);

		_shader = Renderer::instance()->GetShader(1);
		_texScale = Vec2(1, 0.25f);
		_uvOffset = Vec2(0, 3);

		_pressedSound = SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/btnPress.wav");
		_releasedSfx = SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/btnRelease.wav");
		_enterSfx = SoundCtrl::GetInstance()->LoadSFX("Assets/AFX/enterBtn.wav");
		SoundCtrl::GetInstance()->SetSFXVolume(_enterSfx, 25);
	}
	/*
	MouseEvent(new BoxBounds(
		pos + Vec3(-size.x * 0.5f, size.y * 0.5f, 0),
		pos + Vec3(size.x * 0.5f, size.y * 0.5f, 0),
		pos + Vec3(-size.x * 0.5f, -size.y * 0.5f, 0),
		pos + Vec3(size.x * 0.5f, -size.y * 0.5f, 0) ), this) {
	*/
	Button::Button(const char* text, Vec3 pos, Vec3 size, float ang, BaseObject* parent) : Sprite("Assets/Textures/btn.png", pos, size, ang, parent),
		MouseEvent(new BoxBounds(), this) {

		Vec3 texPos = pos;
		texPos.z += 0.1f;
		_txt = new Text(Vec3(0, 0, 0.11f), 0.0f, 6, text);
		_txt->SetInheritTransform(1, false);
		AddChild(_txt);
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
		std::cout << "deleting button\n";
		delete _txt;
	}
	void Button::BeforeDraw() {
		Sprite::BeforeDraw();
		glUniform2f(glGetUniformLocation(_shader->ID, "uvOff"), _uvOffset.x, _uvOffset.y);
		glUniform2f(glGetUniformLocation(_shader->ID, "uv_scale"), _texScale.x, _texScale.y);
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
}