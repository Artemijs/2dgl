#include "Projects/UI/BasePanelTest/BasePanelTest.h"
#include "Graphics/Renderer.h"
#include "Graphics/Materials/MaterialSprite.h"
#include "UI/Button.h"
#include "UI/Text.h"

/*
*
*	ui_panel
*		- dock it
*		- tab it
*		- sclae it
	the top down level editor has to :
		- Select Tile
		- Select texture to paint with
		- Change tile texture byte data to selexcted byte data
		- Save Texture


	GENERAL UI SHIT
		- for convinience you can add a MAkeElementList(newTiem, position offset, alignment) and it will position ui elements for you a bit like html
*/

BasePanelTest::BasePanelTest(){
	_r = Renderer::instance();
	Camera* camera = Renderer::instance()->GetCamera();
	camera->CalculateViewMatrix();
	//this should be in camera
	//(*_r->GetProjection()) = Matrix4x4::Perspective(Utility::Deg2Rad(45), _r->GetWindowSize().x / _r->GetWindowSize().y, 0.1f, 1000.0f);

	
	//something to orient around
	BaseNode* s1 = new BaseNode(Vec3(0, 0, -1), Vec3(10, 10, 1), Vec3(0.0, 0, 0));
	s1->AddComponent<Sprite>(new Sprite(new MaterialSprite(_r->GetShader(7), ASSETS"Textures/default.png")));
	_world->AddChild(s1);
	s1->SetInheritTransform(false, false, false);
	CreatePanels();
	

}


BasePanelTest::~BasePanelTest() {
	
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
		if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_PRESS) {
			_mouse->SetCursorHidden(true);
			c->LockCursor(true);
			c->MouseMove();
		}
		if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_RELEASE) {
			_mouse->SetCursorHidden(false);
			c->LockCursor(false);
		}
	}
	move = c->GetCursorLockState();
	//								move camera
	if (move) {
		if (Keyboard::GetKey('w')->state == KeyState::KEY_DOWN) {
			moveDir = c->GetOrientation() * -1;
			update = true;
		}
		if (Keyboard::GetKey('a')->state == KeyState::KEY_DOWN) {
			moveDir = Vec3::Cross(c->GetOrientation(), Vec3(0, 1.0f, 0));
			update = true;
		}
		if (Keyboard::GetKey('s')->state == KeyState::KEY_DOWN) {
			moveDir = c->GetOrientation();
			update = true;
		}
		if (Keyboard::GetKey('d')->state == KeyState::KEY_DOWN) {
			moveDir = Vec3::Cross(c->GetOrientation(), Vec3(0, 1.0f, 0)) * -1;
			update = true;
		}

		if (update) {
			moveDir.Normalize();
			c->SetPosition(pos + (moveDir * moveSpeed));
		}
	}

}

#include "UI/UIHandler.h"
void BasePanelTest::CreatePanels() {

	Vec2 winSize = _r->GetWindowSize();
	//BasePanel* topPanel = UIHandler::GetPanel("Empty", _world, Vec3(winSize.x * 0.5, winSize.y - 50.0f, -1.0f), Vec3(winSize.x, 100.0f, 1.0f));
	//BasePanel* botPanel = UIHandler::GetPanel("Empty", _world, Vec3(winSize.x * 0.5, 20.0f, -1.0f), Vec3(winSize.x, 40.0f, 1.0f));
	Vec3 mainPanelPos = Vec3(winSize.x * 0.5f, winSize.y * 0.5f - 30.0f, -1.0f);
	//Vec3 mainPanelSize = Vec3(winSize.x, winSize.y - 140.0f, 1.0f);
	Vec3 mainPanelSize = Vec3(winSize.x*0.5f, 700, 1.0f);
	BasePanel* mainPanel = UIHandler::GetPanel("Empty", _world, mainPanelPos, mainPanelSize);
	//BaseNode* bn = new BaseNode(Vec3(0, 0, 0), Vec3(1,1,1), 0);
	

	//topPanel->AddNeighbour(mainPanel, 3);
	//topPanel->SetBackgroundColor(Vec3(0.1f, 0.01f, 0.012f));
	
	//botPanel->AddNeighbour(mainPanel, 1);
	//botPanel->SetBackgroundColor(Vec3(0.17f, 0.14f, 0.178f));

	//mainPanel->AddNeighbour(topPanel, 1);
	//mainPanel->AddNeighbour(botPanel, 3);
	mainPanel->SetBackgroundColor(Vec3(0.1f, 0.1f, 0.1f));
	
	//											BUTTON
	BaseNode* btn = new Button("Close", Vec3(0.0f, -325.0f, -10.0f), Vec3(100.0f, 50.0f, 0), 0.0f);
	btn->SetInheritTransform(true, false, false);
	BaseNode* mainBn = mainPanel->GetParentAsNode();
	mainBn->AddChild(btn);
	//											TITLE
	BaseNode* txtNode = new BaseNode( Vec3(0, 300, 0), Vec3(0, 0, 0), 0);
	txtNode->SetInheritTransform(true, false, false);
	mainBn->AddChild(txtNode);
	txtNode->AddComponent<Text>(new Text("Inventory", txtNode, 20));

	//											inventory items
	Vec3 pos = Vec3(0, 250, 0);
	Vec3 size = Vec3(1, 1, 1);
	for (int i = 0; i < 10; i++) {
		BaseNode* itmNode = new BaseNode(pos, size, 0);
		itmNode->SetInheritTransform(true, false, false);
		mainBn->AddChild(itmNode);
		itmNode->AddComponent<Text>(new Text("Item "+ std::to_string(i), itmNode, 15));
		pos.y -= 25;
	}
	

	//bn->AddChild(btn);

}

//AM I CREATIN A NEW CO ORDINATE SYS?TEM WITH MY MATRICES 
//or
//IS THE TEXTURE POSITION OF A SMALLER FRAME TEXTURE SIZE SCREWING ME OVER?
// maybe i have to use a different projection matrxi for each of these
/*
350 450
450 450
450 350
350 350
*/
