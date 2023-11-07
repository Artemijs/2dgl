#include "./BasePanelTest.h"
#include "../../../Graphics/Renderer.h"




BasePanelTest::BasePanelTest(){
	_r = Renderer::instance();
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
	
	


	MoveCamera3D();

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
	_topPanel = new BasePanel("Empty", _world, Vec3(0, winSize.y * 0.5f, 0.0f), Vec3(winSize.x, 100, 1));
	_topPanel->AddNeighbour(_mainPanel, 3);
}


void BasePanelTest::CreateBotPanel() {

	Vec2 winSize = _r->GetWindowSize();
	_botPanel = new BasePanel("Empty", _world, Vec3(0, winSize.y * 0.5f - 100, 0.0f), Vec3(winSize.x, winSize.y-200, 1));
	_botPanel->AddNeighbour(_mainPanel, 1);
}


void BasePanelTest::CreateMainPanel() {

	Vec2 winSize = _r->GetWindowSize();
	_mainPanel = new BasePanel("Empty", _world, Vec3(0, winSize.y * 0.5f, 0.0f), Vec3(winSize.x, 100, 1));
	_mainPanel->AddNeighbour(_topPanel, 1);
	_mainPanel->AddNeighbour(_botPanel, 3);

}