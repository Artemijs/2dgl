#include "./RayCastTest.h"
#include "../../../Graphics/Renderer.h";
#include "../../../Graphics/Materials/DiffuseMaterial.h"
#include "../../../Graphics/Materials/MaterialSprite.h"
#include "../../../Game/Mesh/MeshLoader.h"
RayCastTest::RayCastTest() {
	//create a plane
	Renderer* r = Renderer::instance();
	_3d = false;
	_fov = Utility::Deg2Rad(90);
	_near = 0.1f;
	_far = 1000.0f;
	_aspect = r->GetWindowSize().x / r->GetWindowSize().y;
	x = 0;

		

	bn1 = new BaseNode(Vec3(100, 100, -500), Vec3(100, 100, 1), 0);
	//Material* m = new MaterialUiSprite();
	bn1->AddComponent<Sprite>(new Sprite(new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png")));
	_world->AddChild(bn1);

	BaseNode* bn = new BaseNode(Vec3(100, 100, -550), Vec3(100, 100, 1), 0);
	//Material* m = new MaterialUiSprite();
	bn->AddComponent<Sprite>(new Sprite(new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png")));
	_world->AddChild(bn);


	Mesh* m = new Mesh(6, r->GetVAO(), new MaterialSprite(Renderer::instance()->GetShader(7), "Assets/Textures/default.png"));


}

RayCastTest::~RayCastTest() {

}

void RayCastTest::Update(float deltaTime) {
	Game::Update(deltaTime);										
																	
	
	if (_3d) {
		(*Renderer::instance()->GetProjection()) = Matrix4x4::Perspective(_fov, _aspect, _near, _far);
		//_fov += Utility::Deg2Rad(1);
	}
	
}
void RayCastTest::MoveCamera(const unsigned int dir) {
	const float moveSpeed = 100;
	Camera* c = Renderer::instance()->GetCamera();
	Vec3 pos = c->GetPosition();
	Vec3 moveDir;
	if (dir == 0) { //w
		moveDir = c->GetOrientation();
		Utility::PrintVector(" W : ", moveDir);
	}
	else if (dir == 1) {//a
		moveDir = Vec3::Cross(c->GetOrientation(), Vec3(0, 1.0f, 0));
		Utility::PrintVector(" A : ", moveDir);
	}
	else if (dir == 2) {//s
		moveDir = c->GetOrientation()*-1;
		Utility::PrintVector(" S : ", moveDir);
	}
	else {//d
		moveDir = Vec3::Cross(c->GetOrientation(), Vec3(0, 1.0f, 0)) * -1;
		Utility::PrintVector(" D : ", moveDir);
	}

	c->SetPosition(pos + (moveDir * moveSpeed));



}
void RayCastTest::HandleKeyInputs(int key, int action, int mods) {
	if (action == 2) return;
	if (action == 0) {
		std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
		switch (key)
		{
		case 87:
			MoveCamera(0);
			break;
		case 65:
			MoveCamera(1);
			break;
		case 83:
			MoveCamera(2);
			break;
		case 68:
			MoveCamera(3);
			break;
			//left
		case 263:
			Renderer::instance()->GetCamera()->SetPosition(Renderer::instance()->GetCamera()->GetPosition() + Vec3(10, 0, 0));
			break;
			//right
		case 262:
			Renderer::instance()->GetCamera()->SetPosition(Renderer::instance()->GetCamera()->GetPosition() + Vec3(-10, 0, 0));
			break;
			//space
		case 32:
			ChangePerspective();
			break;
		default:
			break;
		}

	}
}

void RayCastTest::TurnCamera(const bool dir) {
	return;
	Camera* c = Renderer::instance()->GetCamera();

	//I HAVE TO FIGURE OUT HOW TO ROTATE THS BY A DEGREE AND AN PLANE

	Vec3 lookDir = c->GetOrientation();
	Vec3 newLookDir = Matrix3x3::RotationMatrix(Utility::Deg2Rad(0.1f), Vec3(0, 1, 0)) * lookDir;
	newLookDir.Normalize();
	c->SetOrientation(newLookDir);

}

void RayCastTest::ChangePerspective() {
	_3d = !_3d;

	if (_3d) {
		//swotch to pespective 
		
		(*Renderer::instance()->GetProjection() )= Matrix4x4::Perspective(_fov, _aspect, _near, _far);
	}
	else {
		//switch to ortho
		Vec2 wh = Renderer::instance()->GetWindowSize();
		(*Renderer::instance()->GetProjection()) = Matrix4x4::Ortho(0.0f, wh.x, 0.0f, wh.y, 0.1f, 1000.0f);
	}
}