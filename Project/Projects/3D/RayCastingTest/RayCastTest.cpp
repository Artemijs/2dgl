#include "./RayCastTest.h"
#include "../../../Graphics/Renderer.h";
#include "../../../Graphics/Materials/DiffuseMaterial.h"
RayCastTest::RayCastTest() {
	//create a plane
	Renderer* r = Renderer::instance();
	_3d = false;
	_fov = Utility::Deg2Rad(90);
	_near = 0.1f;
	_far = 1000.0f;
	_aspect = r->GetWindowSize().x / r->GetWindowSize().y;


	BaseNode* bn = new BaseNode(Vec3(10, 100, -200), Vec3(100, 100, 1), 0);
	Material* m = new MaterialUiSprite();
	bn->AddComponent<Sprite>(new Sprite(m));
	_world->AddChild(bn);

	BaseNode* bn1 = new BaseNode(Vec3(0, 0, -500), Vec3(100, 100, 1), 0);
	//Material* m = new MaterialUiSprite();
	bn1->AddComponent<Sprite>(new Sprite(new MaterialUiSprite()));
	_world->AddChild(bn1);
}

RayCastTest::~RayCastTest() {

}

void RayCastTest::Update(float deltaTime) {
	Game::Update(deltaTime);
	if (_3d) {
		(*Renderer::instance()->GetProjection()) = Matrix4x4::Perspective(_fov, _aspect, _near, _far);
		_fov += Utility::Deg2Rad(1);
	}
}
void RayCastTest::HandleKeyInputs(int key, int action, int mods) {
	if (action == 2) return;
	if (action == 0) {
		std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
		switch (key)
		{
		/*case 49:
			CollisionDetection::_print = true;
			//left
		case 263:
			Rotate(1);
			break;
			//right
		case 262:
			Rotate(-1);
			break;
			//space
		case 32:
			Play(!_play);
			break;
		case 80://n
			PrevTest();
			break;
		case 78://p
			NextTest();
			break;*/
		case 32:
			ChangePerspective();
			break;
		default:
			break;
		}

	}
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