#include "./TopDownEditor.h"
#include "../../Graphics/Renderer.h";
#include "../../Game/Mesh/MeshLoader.h"
#include "../../Graphics/Materials/MaterialSprite.h"

TopDownEditor::TopDownEditor(): _heightBTBG(10), _widthBTBG(10) {
	CreateNew();
	Renderer* r = Renderer::instance();
	(*r->GetProjection()) = Matrix4x4::Perspective(Utility::Deg2Rad(90), r->GetWindowSize().x / r->GetWindowSize().y, 0.1f, 1000.0f);
}


TopDownEditor::~TopDownEditor() {

}


void TopDownEditor::Update(float deltaTime) {
	Game::Update(deltaTime);
	Renderer* r = Renderer::instance();
	Camera* c = r->GetCamera();
	
	

	MoveCamera3D();
	//MoveCamera2D();
}


void TopDownEditor::MoveCamera3D(bool rotate, bool move) {

	const float moveSpeed = 1.2f;
	Camera* c = Renderer::instance()->GetCamera();
	Vec3 pos = c->GetPosition();
	Vec3 moveDir = Vec3();
	bool update = false;

	if (rotate) {
		//							rotate camera
		if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_HELD) {
			_mouse->SetCursorHidden(true);
			c->LockCursor(true);
			c->MouseMove();
		}
		if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_UP) {
			_mouse->SetCursorHidden(false);
			c->LockCursor(false);
		}
	}
	move = c->GetCursorLockState();
	//								move camera
	if (move) {
		if (Keyboard::GetKey('w')->state == KeyState::KEY_HELD) {
			moveDir = c->GetOrientation() * -1;
			update = true;
		}
		if (Keyboard::GetKey('a')->state == KeyState::KEY_HELD) {
			moveDir = Vec3::Cross(c->GetOrientation(), Vec3(0, 1.0f, 0));
			update = true;
		}
		if (Keyboard::GetKey('s')->state == KeyState::KEY_HELD) {
			moveDir = c->GetOrientation();
			update = true;
		}
		if (Keyboard::GetKey('d')->state == KeyState::KEY_HELD) {
			moveDir = Vec3::Cross(c->GetOrientation(), Vec3(0, 1.0f, 0)) * -1;
			update = true;
		}

		if (update) {
			moveDir.Normalize();
			c->SetPosition(pos + (moveDir * moveSpeed));
		}
	}

}


void TopDownEditor::MoveCamera2D() {
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

	//							something to orient around 
	BaseNode* bn1 = new BaseNode(Vec3(0, 0, 0), Vec3(10, 10, 1), 0);
	//Material* m = new MaterialUiSprite();
	//bn1->AddComponent<Sprite>(new Sprite(new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png")));
	bn1->AddComponent<Sprite>(new Sprite(new MaterialSprite()));
	_world->AddChild(bn1);

	
	//							CREATE MAIN TILE MESH

	//initialize base node 
	_mainTileMesh = new BaseNode(Vec3(0,0,0), Vec3(10, 10, 1), 0);
	_world->AddChild(_mainTileMesh);
	
	//initialize the mesh
	Mesh* m ;
	m = MeshLoader::GetPlane(2, 2);
	
	_mainTileMesh->AddComponent<Mesh>(m);
	
	
}































TesObject::TesObject() {
	test = 69;
	testPtr = new int(67 + 2);
}
TesObject::~TesObject() {
	printf("deleteingn TEST OBJECT\n");
	delete testPtr;
}



TesObjecTChild::TesObjecTChild() : TesObject() {

}
TesObjecTChild::~TesObjecTChild() {
	printf("deleteingn TEST OBJECT CHILD\n");
	
}



GarbageCollectorTest::GarbageCollectorTest() {
	
	Memory* m = new TesObjecTChild();

	delete m;


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
	MemoryManager::Clean();




}


GarbageCollectorTest::~GarbageCollectorTest() {

}


void GarbageCollectorTest::Update(float deltaTime) {
	Game::Update(deltaTime);

}











QuaternionTest::QuaternionTest() {
	node = new BaseNode(Vec3(), Vec3(400, 400, 1), 0);
	Sprite* s = new Sprite(new MaterialSprite());
	node->AddComponent<Sprite>(s);
	_world->AddChild(node);

	Renderer* r = Renderer::instance();
	(*r->GetProjection()) = Matrix4x4::Perspective(Utility::Deg2Rad(90), r->GetWindowSize().x / r->GetWindowSize().y, 0.1f, 1000.0f);
}


QuaternionTest::~QuaternionTest() {

}


void QuaternionTest::Update(float deltaTime) {
	Game::Update(deltaTime);
	Renderer* r = Renderer::instance();
	Camera* c = r->GetCamera();

	Quaternion q(Utility::Deg2Rad(45), Vec3(0.0f,1.0f,0.0f));
	
	//node->GetTransform()._angle = q.GetEulerAngles();
	Transform& t = node->GetTransform();
	//t._angle = Vec3(0.0f, Utility::Deg2Rad(45), 0.0f);
	t._angle = q.GetEulerAngles();;
	node->SetAngle(Vec3(0.0f, Utility::Deg2Rad(45), 0.0f));
	MoveCamera3D();
}


void QuaternionTest::MoveCamera3D(bool rotate, bool move) {

	const float moveSpeed = 1.2f;
	Camera* c = Renderer::instance()->GetCamera();
	Vec3 pos = c->GetPosition();
	Vec3 moveDir = Vec3();
	bool update = false;

	if (rotate) {
		//							rotate camera
		if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_HELD) {
			_mouse->SetCursorHidden(true);
			c->LockCursor(true);
			c->MouseMove();
		}
		if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_UP) {
			_mouse->SetCursorHidden(false);
			c->LockCursor(false);
		}
	}
	move = c->GetCursorLockState();
	//								move camera
	if (move) {
		if (Keyboard::GetKey('w')->state == KeyState::KEY_HELD) {
			moveDir = c->GetOrientation() * -1;
			update = true;
		}
		if (Keyboard::GetKey('a')->state == KeyState::KEY_HELD) {
			moveDir = Vec3::Cross(c->GetOrientation(), Vec3(0, 1.0f, 0));
			update = true;
		}
		if (Keyboard::GetKey('s')->state == KeyState::KEY_HELD) {
			moveDir = c->GetOrientation();
			update = true;
		}
		if (Keyboard::GetKey('d')->state == KeyState::KEY_HELD) {
			moveDir = Vec3::Cross(c->GetOrientation(), Vec3(0, 1.0f, 0)) * -1;
			update = true;
		}

		if (update) {
			moveDir.Normalize();
			c->SetPosition(pos + (moveDir * moveSpeed));
		}
	}

}
