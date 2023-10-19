#include "./TopDownEditor.h"
#include "../../Graphics/Renderer.h";
#include "../../Game/Mesh/MeshLoader.h"


TopDownEditor::TopDownEditor(): _heightBTBG(10), _widthBTBG(10) {
}


TopDownEditor::~TopDownEditor() {

}


void TopDownEditor::Update(float deltaTime) {
	Game::Update(deltaTime);
	Renderer* r = Renderer::instance();
	Camera* c = r->GetCamera();
	
	

	MoveCamera();

}


void TopDownEditor::MoveCamera() {

	const float moveSpeed = 1.2f;
	Camera* c = Renderer::instance()->GetCamera();
	Vec3 pos = c->GetPosition();
	Vec3 moveDir = Vec3();
	bool update = false;

	//								move camera
	if (Keyboard::GetKey('w')->state == KeyState::KEY_HELD) {
		moveDir.y = 1;
		update = true;
	}
	if (Keyboard::GetKey('a')->state == KeyState::KEY_HELD) {
		moveDir.x = -1;
		update = true;
	}
	if (Keyboard::GetKey('s')->state == KeyState::KEY_HELD) {
		moveDir.y = -1;
		update = true;
	}
	if (Keyboard::GetKey('d')->state == KeyState::KEY_HELD) {
		moveDir.x = 1;
		update = true;
	}
	
	if (update) {
		moveDir.Normalize();
		c->SetPosition(pos + (moveDir * moveSpeed));
	}

}


void TopDownEditor::CreateNew() {
	//CREATE MAIN TILE MESH
	Mesh* m ;
	m = MeshLoader::GetPlane(10, 1, 1);
	//m->SetMaterial(
	_mainTileMesh = new BaseNode(Vec3(), Vec3(400, 400, 1), 0);




	
	
}
