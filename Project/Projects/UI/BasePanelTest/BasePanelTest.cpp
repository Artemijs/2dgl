#include "./BasePanelTest.h"
#include "../../../Graphics/Renderer.h"
#include "../../../Graphics/Materials/MaterialSprite.h"



BasePanelTest::BasePanelTest(){
	_r = Renderer::instance();
	Camera* camera = Renderer::instance()->GetCamera();
	camera->CalculateViewMatrix();
	//this should be in camera
	//(*_r->GetProjection()) = Matrix4x4::Perspective(Utility::Deg2Rad(45), _r->GetWindowSize().x / _r->GetWindowSize().y, 0.1f, 1000.0f);

	_world->GetComponent<FBOComponent>()->SetClearColor(Vec3(1.0f, 1.0f, 1.0f));
	//something to orient around
	BaseNode* s1 = new BaseNode(Vec3(0, 0, -1), Vec3(100, 100, 1), Vec3(0.0, 0, 0));
	s1->AddComponent<Sprite>(new Sprite(new MaterialSprite(_r->GetShader(7), "Assets/Textures/default.png")));
	_world->AddChild(s1);
	CreateTopPanel();
	CreateMainPanel();
	CreateBotPanel();
	

}


BasePanelTest::~BasePanelTest() {
	delete _topPanel;
	delete _botPanel;
	delete _mainPanel;
}


void BasePanelTest::Update(float deltaTime) {
	Game::Update(deltaTime);
	
	


	//MoveCamera3D(false);

}


void BasePanelTest::MoveCamera3D(bool rotate, bool move) {

	const float moveSpeed = 0.05f;
	Camera* c =_r->GetCamera();
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


void BasePanelTest::CreateTopPanel() {

	Vec2 winSize = _r->GetWindowSize();
	_topPanel = new BasePanel("Empty", _world, Vec3(winSize.x * 0.5, winSize.y -50.0f, -1.0f), Vec3(winSize.x, 100.0f, 1.0f));
	_topPanel->AddNeighbour(_mainPanel, 3);
	_topPanel->SetBackgroundColor(Vec3(0.1f, 0.01f, 0.012f));
}


void BasePanelTest::CreateBotPanel() {

	Vec2 winSize = _r->GetWindowSize();
	_botPanel = new BasePanel("Empty", _world, Vec3(winSize.x * 0.5, 20.0f, -1.0f), Vec3(winSize.x, 40.0f, 1.0f));
	_botPanel->AddNeighbour(_mainPanel, 1);
	_botPanel->SetBackgroundColor(Vec3(0.17f, 0.14f, 0.178f));
}


void BasePanelTest::CreateMainPanel() {

	Vec2 winSize = _r->GetWindowSize();
	_mainPanel = new BasePanel("Empty", _world, Vec3(winSize.x * 0.5f, winSize.y *0.5f - 30.0f , -1.0f), Vec3(winSize.x, winSize.y - 140.0f, 1.0f));
	_mainPanel->AddNeighbour(_topPanel, 1);
	_mainPanel->AddNeighbour(_botPanel, 3);
	_mainPanel->SetBackgroundColor(Vec3(0.1f, 0.1f, 0.1f));

}