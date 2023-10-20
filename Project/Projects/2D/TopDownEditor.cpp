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































TesObject::TesObject() {
	test = 69;
	testPtr = new int(67 + 2);
}
TesObject::~TesObject() {
	printf("deleteingn TEST OBJECT\n");
	delete testPtr;
}



GarbageCollectorTest::GarbageCollectorTest() {

	SList<TesObject*>* list = new SList<TesObject*>();
	TesObject* a = new TesObject();
	TesObject* b = new TesObject();
	TesObject* c = new TesObject();
	TesObject* d = new TesObject();
	TesObject* e = new TesObject();
	TesObject* f = new TesObject();
	/*SList<Memory*>* list = new SList<Memory*>();
	Memory* a = new Memory();
	Memory* b = new Memory();
	Memory* c = new Memory();
	Memory* d = new Memory();
	Memory* e = new Memory();
	Memory* f = new Memory();*/

	list->Add(a);
	list->Add(b);
	list->Add(c);
	list->Add(d);
	list->Add(e);
	list->Add(f);

	delete list;
	MemoryManager::ClearMemory();




}


GarbageCollectorTest::~GarbageCollectorTest() {

}


void GarbageCollectorTest::Update(float deltaTime) {
	Game::Update(deltaTime);

}