#include "RenderNodeTest.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Materials/MaterialSprite.h"
#include "../../Game/RenderNode.h"
using namespace RNT;



RenderNodeTest::RenderNodeTest(){
	
	Renderer* r = Renderer::instance();
	Camera* camera = Renderer::instance()->GetCamera();
	//set camera perspectie
	(*r->GetProjection()) = Matrix4x4::Perspective(Utility::Deg2Rad(100), r->GetWindowSize().x / r->GetWindowSize().y, 0.1f, 1000.0f);

	//set up camera 
	//camera->SetPosition(Vec3(0.0f, 0.0f, 10.0f));
	//camera->SetOrientation(Vec3(0.0f, 0.0f, -1.0f));
	camera->CalculateViewMatrix();

	//				set up render nodes
	SetUp();

}


RenderNodeTest::~RenderNodeTest() {

}


void RenderNodeTest::Update(float deltaTime) {
	Game::Update(deltaTime);
	Renderer* r = Renderer::instance();
	Camera* c = r->GetCamera();


	
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
///				--s1
///			--s2
/// </summary>
void RenderNodeTest::SetUp() {
	Renderer* r = Renderer::instance();
	//s1
	BaseNode* s1 = new BaseNode(Vec3(0,0,-1), Vec3(1,1, 1), Vec3(0.0,0,0));
	s1->AddComponent<Sprite>(new Sprite(new MaterialSprite(r->GetShader(7),"Assets/Textures/default.png")));
	_world->AddChild(s1);

	//r1
	RenderNode* rn1 = new RenderNode(Vec3(10, 10, 0), Vec3(100, 100, 1), 0.0f);
	_world->AddChild(rn1);

	//r1 -- s1
	BaseNode* r1s1 = new BaseNode(Vec3(0, 0, -1), Vec3(1, 2, 1), Vec3(0.0, 0, 0));
	r1s1->AddComponent<Sprite>(new Sprite(new MaterialSprite(r->GetShader(7), "Assets/Textures/default.png")));
	rn1->AddChild(r1s1);

	//s2
	BaseNode* s2 = new BaseNode(Vec3(2, 0, -1), Vec3(1, 1, 1), Vec3(0.0, 0, 0));
	s2->AddComponent<Sprite>(new Sprite(new MaterialSprite(r->GetShader(7), "Assets/Textures/default.png")));
	_world->AddChild(s2);
}