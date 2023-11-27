#include "RenderNodeTest.h"

#include "../../Graphics/Materials/MaterialSprite.h"
#include "../../Game/RenderNode.h"
#include "../../UI/Text.h"
using namespace RNT;



RenderNodeTest::RenderNodeTest(){
	
	Renderer* r = Renderer::instance();
	Camera* camera = Renderer::instance()->GetCamera();
	_rn1 = NULL;
	//set camera perspectie
	(*r->GetProjection()) = Matrix4x4::Perspective(Utility::Deg2Rad(45), r->GetWindowSize().x / r->GetWindowSize().y, 0.1f, 1000.0f);

	//set up camera 
	//camera->SetPosition(Vec3(0.0f, 0.0f, 10.0f));
	//camera->SetOrientation(Vec3(0.0f, 0.0f, -1.0f));
	camera->CalculateViewMatrix();

	//				set up render nodes
	//SetUpB();
	ButtonInNode();
	

}


RenderNodeTest::~RenderNodeTest() {

}


void RenderNodeTest::Update(float deltaTime) {
	Game::Update(deltaTime);
	Renderer* r = Renderer::instance();
	Camera* c = r->GetCamera();

	if(_rn1 != NULL)
		_rn1->SetPosition(_mouse->GetMousePosV3() - Vec3(0,0 , 1.0f));
	MoveCamera3D();
	//MoveCamera2D();

}


void RenderNodeTest::MoveCamera3D(bool rotate, bool move) {

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


void RenderNodeTest::MoveCamera2D() {
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

/// <summary>
/// world	-- s1
///			-- rn1
///				||--s1
///			--s2
/// </summary>
void RenderNodeTest::SetUp() {
	Renderer* r = Renderer::instance();
	//s1
	BaseNode* s1 = new BaseNode(Vec3(0,0,-1), Vec3(1, 1, 1), Vec3(0.0f, 0.0f, 0.0f));
	s1->AddComponent<Sprite>(new Sprite(new MaterialSprite(r->GetShader(7),"Assets/Textures/default.png")));
	_world->AddChild(s1);

	//r1
	RenderNode* rn1 = new RenderNode(Vec3(100, 100, -10), Renderer::instance()->WindowSizeVec3(), 0);
	_world->AddChild(rn1);

	//r1 -- s1
	BaseNode* r1s1 = new BaseNode(Vec3(0, 0, -1), Vec3(1, 2, 1), Vec3(0.0, 0, 0));
	r1s1->AddComponent<Sprite>(new Sprite(new MaterialSprite(r->GetShader(7), "Assets/Textures/default.png")));
	rn1->AddChild(r1s1);
	
	//s2
	BaseNode* s2 = new BaseNode(Vec3(-1, 0, -1), Vec3(1, 1, 1), Vec3(0.0, 0, 0));
	s2->AddComponent<Sprite>(new Sprite(new MaterialSprite(r->GetShader(7), "Assets/Textures/default.png")));
	_world->AddChild(s2);

	_world->GetComponent<FBOComponent>()->SetClearColor(Vec3(1.0f, 1.0f, 1.0f));
}

/// <summary>
/// world	
///			-- rn1
///				||	--s1
///					--s2
///			--s1
///			--s2
/// </summary>
void RenderNodeTest::SetUpB() {
	Renderer* r = Renderer::instance();
	
	//r1
	Vec3 fboSize = Vec3(400, 400, 0);
	Vec3 fboSize2 = Renderer::instance()->WindowSizeVec3();
	RenderNode* rn1 = new RenderNode(Vec3(200, 400, -1), fboSize, 0);// Renderer::instance()->WindowSizeVec3(), 0);
	_world->AddChild(rn1);

	//r1 -- s1
	BaseNode* r1s1 = new BaseNode(Vec3(0, 0, -1), Vec3(1, 2, 1), Vec3(0.0f, 0.0f, 0.0f));
	r1s1->AddComponent<Sprite>(new Sprite(new MaterialSprite(r->GetShader(7), "Assets/Textures/temp.png")));
	rn1->AddChild(r1s1);
	
	//r1 -- s2
	BaseNode* r1s2 = new BaseNode(Vec3(55, 110, -1), Vec3(100, 200, 1), Vec3(0.0f, 0.0f, 0.0f));
	r1s2->AddComponent<Sprite>(new Sprite(new MaterialUiSprite(r->GetShader(2), "Assets/Textures/sliderPinDefault.png")));
	rn1->AddChild(r1s2);

	//s1
	BaseNode* s1 = new BaseNode(Vec3(0, 0, -1), Vec3(1, 1, 1), Vec3(0.0, 0, 0));
	s1->AddComponent<Sprite>(new Sprite(new MaterialSprite(r->GetShader(7), "Assets/Textures/default.png")));
	_world->AddChild(s1);

	//s2
	BaseNode* s2 = new BaseNode(Vec3(-1, 0, -1), Vec3(1, 1, 1), Vec3(0.0, 0, 0));
	s2->AddComponent<Sprite>(new Sprite(new MaterialSprite(r->GetShader(7), "Assets/Textures/default.png")));
	_world->AddChild(s2);
}



#include "../../UI/Button.h"
/// <summary>
/// world	
///			-- bn1
///					--s1
///			-- rn1
///					--r1b1
///					--r1s1
/// </summary>
void RenderNodeTest::ButtonInNode() { 

	Renderer* r = Renderer::instance();
	
	//								sprite parented to a blank node 
	BaseNode* bn1 = new BaseNode(Vec3(0, 0, 0), Vec3(0, 0, 0), 0);
	_world->AddChild(bn1);

	
	BaseNode* s1 = new BaseNode(Vec3(50, 50, -1), Vec3(100.0f, 100.0f, 1.0f), 0.0f);
	s1->SetInheritTransform(false, false, false);
	bn1->AddChild(s1);
	s1->AddComponent<Sprite>(new Sprite(new MaterialUiButton()));
	

	//								text 
	BaseNode* t1 = new BaseNode(Vec3(50, 150, -10), Vec3(0, 0, 1.0f), 0.0f);
	_world->AddChild(t1);
	t1->AddComponent<Text>(new Text("h!", t1));


	//								btn1
	BaseNode* btn1 = new Button("btn1" ,Vec3(400, 400, -1.0f), Vec3(100, 100, 1.0f), 0.0f);
	_world->AddChild(btn1);
	


	
	//								RN!
	Vec3 fboSize = Vec3(400, 400, 0);
	Vec3 fboSize2 = r->WindowSizeVec3();

	_rn1 = new RenderNode(Vec3(0, 0, -1), fboSize, 0);
	
	
	_world->AddChild(_rn1);
	//_rn1->AddChild(s1);
	
	//	I NEED A PROJECTION MATRIX THAT CREATES A NEW CO ORDINATE SYSTEM
	//	FIX TEXT
	

	//								r1 -- b1
	Button* r1b1 = new Button("BTN", Vec3( 150, 150, -2.0f), Vec3(100.0f, 100.0f, 1.0f), 0);
	bool args[3] = { false, false, false };
	r1b1->SetInheritTransform(args);
	//r1b1->AddComponent<Sprite>(new Sprite(new MaterialSprite(r->GetShader(7), "Assets/Textures/temp.png")));

	_rn1->AddChild(r1b1);
	
	BaseNode* r1s1 = new BaseNode(Vec3(50, 50, -1), Vec3(100, 100, 1), Vec3(0.0f, 0.0f, 0.0f));
	r1s1->AddComponent<Sprite>(new Sprite(new MaterialUiSprite( "Assets/Textures/default.png")));
	r1s1->SetInheritTransform(0, true);
	_rn1->AddChild(r1s1);
	
}