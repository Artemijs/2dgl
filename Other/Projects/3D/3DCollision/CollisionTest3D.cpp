#include "Projects/3D/3DCollision/CollisionTest3D.h"
#include "Graphics/Renderer.h";
#include "Graphics/Materials/DiffuseMaterial.h"
#include "Graphics/Materials/MaterialSprite.h"
#include "Game/Mesh/MeshLoader.h"
#include "Math/CollisionHandler.h"


CollisionTest3D::CollisionTest3D() {

}


CollisionTest3D::~CollisionTest3D() {

}


void CollisionTest3D::Update(float deltaTime) {
	Game::Update(deltaTime);
	Renderer* r = Renderer::instance();
	Camera* c = r->GetCamera();
	
	

	MoveCamera();

}


void CollisionTest3D::MoveCamera() {

	const float moveSpeed = 1.2f;
	Camera* c = Renderer::instance()->GetCamera();
	Vec3 pos = c->GetPosition();
	Vec3 moveDir;
	
	//								rotate camera
	if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_PRESS) {
		_mouse->SetCursorHidden(true);
		c->LockCursor(true);
		c->MouseMove();
	}
	if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_RELEASE) {
		_mouse->SetCursorHidden(false);
		c->LockCursor(false);
	}

	//								move camera
	if (Keyboard::GetKey('w')->state == KeyState::KEY_DOWN) {
		moveDir = c->GetOrientation() * -1;
	}
	if (Keyboard::GetKey('a')->state == KeyState::KEY_DOWN) {
		moveDir = Vec3::Cross(c->GetOrientation(), Vec3(0, 1.0f, 0));
		Utility::PrintVector(" A : ", moveDir);
	}
	if (Keyboard::GetKey('s')->state == KeyState::KEY_DOWN) {
		moveDir = c->GetOrientation();
		Utility::PrintVector(" S : ", moveDir);
	}
	if (Keyboard::GetKey('d')->state == KeyState::KEY_DOWN) {
		moveDir = Vec3::Cross(c->GetOrientation(), Vec3(0, 1.0f, 0)) * -1;
		Utility::PrintVector(" D : ", moveDir);
	}
	c->SetPosition(pos + (moveDir * moveSpeed));

}