#include "./TopDownEditor.h"
#include "../../Graphics/Renderer.h";
#include "../../Game/Mesh/MeshLoader.h"
#include "../../Graphics/Materials/MaterialSprite.h"
#include "./TileMapMaterial.h"
#include "../../Math/CollisionHandler.h"
#include "../../Math/BoxBounds.h"




/*
	the top down level editor has to :
		- Select Tile
		- Select texture to paint with
		- Change tile texture byte data to selexcted byte data
		- Save Texture


*/




TopDownEditor::TopDownEditor(): _heightBTBG(10.0f), _widthBTBG(10.0f), _tileSize(50.0f){
	CreateNew();
	Renderer* r = Renderer::instance();
	Camera* camera = Renderer::instance()->GetCamera();
	//set camera perspectie
	//(*r->GetProjection()) = Matrix4x4::Perspective(Utility::Deg2Rad(90), r->GetWindowSize().x / r->GetWindowSize().y, 0.1f, 1000.0f);

	//set up camera 
	camera->SetPosition(Vec3(0.0f, 0.0f, 10.0f));
	camera->SetOrientation(Vec3(0.0f, 0.0f, 1.0f));
	camera->CalculateViewMatrix();
	_moveOver = false;
	//Shader* s = new Shader("Projects/2D/TileMapEditorMain.vert", "Projects/2D/TileMapEditorMain.frag");
	//delete s;


}


TopDownEditor::~TopDownEditor() {

}


void TopDownEditor::Update(float deltaTime) {
	Game::Update(deltaTime);
	Renderer* r = Renderer::instance();
	Camera* c = r->GetCamera();
	
	
	if (_moveOver) {
		HandleMouseMove();
	}
	//MoveCamera3D();
	MoveCamera2D();
	
}


void TopDownEditor::MoveCamera3D(bool rotate, bool move) {

	const float moveSpeed = 0.05f;
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
	const float moveSpeed = 0.2f;
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
		c->CalculateViewMatrix();
	}

}


void TopDownEditor::CreateNew() {
	float ang = Utility::Deg2Rad(45.0f);
	//							something to orient around 
	BaseNode* bn1 = new BaseNode(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
	//Material* m = new MaterialUiSprite();
	//bn1->AddComponent<Sprite>(new Sprite(new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png")));
	bn1->AddComponent<Sprite>(new Sprite(new MaterialSprite()));
	_world->AddChild(bn1);
	BaseNode* bn2 = new BaseNode(Vec3(500.0f, 0.0f, 0.0f), Vec3(100.0f, 10.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
	//Material* m = new MaterialUiSprite();
	//bn1->AddComponent<Sprite>(new Sprite(new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png")));
	bn2->AddComponent<Sprite>(new Sprite(new MaterialSprite()));
	_world->AddChild(bn2);


	
	//							CREATE MAIN TILE MESH

	//initialize base node Utility::Deg2Rad(90.0f)
	
	_mainTileMesh = new BaseNode(Vec3(400.0f, 400.0f, 0), Vec3(400, 400, 1), Vec3(0.0f, 0.0f, 0.0f));
	_world->AddChild(_mainTileMesh);
	
	//initialize the mesh
	Mesh* m ;
	m = MeshLoader::GetPlane(2, 2);

	//initialize tile shader settings
	_tileSize = 100.0f;
	Vec3 outlineColor(0.0f, 1.0f, 0.5f);
	//in pixels
	float outlineSize = 5.0f;

	Vec3 gridLineColor(0.5f, 0.5f, 0.5f);
	//in pixels 
	float gridLineSize = 2.0f;

	//change meshes default material
	BaseMaterial* mem = m->GetMaterial();
	
	//MemoryManager::AddToGarbage(mem);
	garbage(mem);
	_tileMapMat = new TileMapMaterial(_tileSize, _mainTileMesh->GetTransform()._scale.x, gridLineColor, gridLineSize, outlineSize, outlineColor);
	mem = _tileMapMat;
	m->SetMaterial(mem);
	garbage(new Memory());

	_mainTileMesh->AddComponent<Mesh>(m);

	//												add collision event for mouse interaction
	Bounds* box = new BoxBounds(_mainTileMesh, BoundsType::AABB);
	MouseEvent* me = new MouseEvent();
	
	_mainTileMesh->AddComponent(box); 
	_mainTileMesh->AddComponent<MouseEvent>(me);


	//create a LABUDA DURAIVU function
	auto mouseE = [&](const Vec3 mousePos) {
		_moveOver = true;
	};
	auto mouseEE = [&](const Vec3 mousePos) {
		OnMouseLeave(mousePos);
	};
	//add an on enter event
	me->AddEvent(mouseE, BtnEvent::ON_ENTER);
	//on Exit
	me->AddEvent(mouseEE, BtnEvent::ON_LEAVE);

	
	
	
}


void TopDownEditor::HandleMouseMove() {
	
	Vec3 meshSize = _mainTileMesh->GetTransform()._scale;
	Vec3 origin = ((*Renderer::instance()->GetCamera()->GetViewMatrix()) * _mainTileMesh->GetTransform()._position) - (meshSize * 0.5f);
	Vec3 tMouse = _mouse->GetMousePosV3() - origin;
	unsigned int maxTiles = meshSize.x / _tileSize;
	//find the tile i and j (row, col)
	float col = (int)(tMouse.x/_tileSize);
	float row = (int)(tMouse.y/_tileSize);

	_tileMapMat->HighlightTile(row/maxTiles, col/maxTiles);
	printf("ON ENTER %.3f, %.3f\n", col, row);
}


void TopDownEditor::OnMouseLeave(const Vec3& mPos) {
	printf("ON EXIT\n");
	_moveOver = false;
	_tileMapMat->HighlightTile(-1, -1);
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
	//t._position = t._position * q;
	t._angle = q.GetEulerAngles();
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
