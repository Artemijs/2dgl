#include "CollisionTesMain.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Sprite.h"
#include "../../Math/BoxBounds.h"
#include "../../Math/SphereBounds.h"
//
#include "../../UI/Button.h"

CollisionTestMain::CollisionTestMain():Game() {
	
	//Vec2 test = Vec2(5, 10);
	//test.Normalize();

	_myNode = new BaseNode(Vec3(450, 400, 0), Vec3(50, 50, 1), 0);
	Sprite* s = new Sprite("Assets/Textures/Circle.png");
	//s->GetMaterial()
	_myNode->AddComponent(s);
	Bounds* bBox = new SphereBounds(_myNode, 12.5f);
	bBox->_solid = false;		
	_myNode->AddComponent(bBox);
	_world->AddChild(_myNode);	

	
	unsigned int maxNodes = 10;
	_otherNodes = new BaseNode[maxNodes];
	int windowW = Renderer::instance()->GetWindowSize().x;
	int windowH = Renderer::instance()->GetWindowSize().y;

	for (int i = 0; i < maxNodes; i++) {

		Vec3 randPos = Vec3(rand() % windowW, rand() % windowH, 0);
		int rRad = 50;// rand() % 100;
		BaseNode* b = new BaseNode(randPos, Vec3(rRad, rRad, 1), 0);
		b->AddComponent(new Sprite("Assets/Textures/Circle.png"));
		Bounds* bBox = new SphereBounds(b, 12.5f);
		bBox->_solid = false;
		b->AddComponent(bBox);
		
		_otherNodes->AddChild(b);
		_world->AddChild(b);
	}



/*

	Bounds* aBox = _myNode->GetComponent<Bounds>();
	aBox->AddEvent(true, new CollisionEvent(bBox, []( Bounds* a,  Bounds* b, SeparationData& sd) {
		printf("HELLO WORLD from a collisiion event\n");
	}));


	aBox->AddEvent(false, new CollisionEvent(bBox, [](Bounds* a, Bounds* b, SeparationData& sd) {
		printf("EXIT COLLISION EVENTO\n");
	}));
	aBox->_isFixed = true;
	//b->AddComponent(new Sprite("Assets/Textures/default.png"));
	//b->AddComponent(new BoxBounds());
	
	
	_world->AddChild(a);
	
	_world->AddChild(b);
	*/
	//CreateTests(a, b);
	//_state = 0;
	_play = false;

	_angVel = 0;
	_ang = 0;
	//_angChange = 2;



/*BaseNode* circle = new BaseNode(Vec3(100, 100, 0), Vec3(50, 50, 1), 0);
	circle->AddComponent(new Sprite("Assets/Textures/Circle.png"));
	Bounds* crclBounds = new SphereBounds(circle, 25);
	
	circle->AddComponent(crclBounds);
	_world->AddChild(circle);*/


}


CollisionTestMain::~CollisionTestMain() {
	std::cout << "deleting CollisionDetection\n";
	delete _world;
	delete _otherNodes;
}
//263 left
//262 right 
// 32 space 
#include "../../Math/CollisionDetection.h"
void CollisionTestMain::HandleKeyInputs(int key, int action, int mods) {
	if (action == 2) return;
	if (action == 0) {
		std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
		switch (key)
		{
		case 49:
			CollisionDetection::_print = true;
			//left
		case 263:
			//Rotate(1);
			break;
			//right
		case 262:
			//Rotate(-1);
			break;
			//space
		case 32:
			Play(!_play);
			break;
		case 80://n
			//PrevTest();
			break;
		case 78://p
			//NextTest();
			break;
		default:
			break;
		}
		
	}
}

void CollisionTestMain::Update(float deltaTime) {
	Game::Update(deltaTime);
	if (!_play) return;
	



}

void CollisionTestMain::Play(const bool on) {
	_play = on;
}








//LINE INTERSECTION TEST





IneIntersectTest::IneIntersectTest() :Game() {
	Vec2 res = Vec2::LineIntersection(
		Vec2(0, 0),
		Vec2(3, 3),
		Vec2(3, 0),
		Vec2(0, 3));
	Utility::PrintVector("Result of intersection :", res);
	res = Vec2::LineIntersection(
		Vec2(0, 0),
		Vec2(3, 3),
		Vec2(3, 0),
		Vec2(6, 3));
	Utility::PrintVector("Result of intersection :", res);

}


IneIntersectTest::~IneIntersectTest() {
	std::cout << "deleting CollisionDetection\n";
	//delete _world;
	
}
//263 left
//262 right 
// 32 space 
#include "../../Math/CollisionDetection.h"
void IneIntersectTest::HandleKeyInputs(int key, int action, int mods) {

}

void IneIntersectTest::Update(float deltaTime) {
	Game::Update(deltaTime);





}

void IneIntersectTest::Play(const bool on) {
	
}


//Material  TEST




/// <summary>
/// CANNOT SET MATERIAL
/// </summary>
MaterialTest::MaterialTest() :Game() {
	Renderer* r = Renderer::instance();
	//button
	float startX = 200;
	float startY = 100;
	Vec3 size = Vec3(200, 75, 1);
	
	BaseNode* btn = new Button("Hi!", Vec3(startX, startY, 0), size, 0);
	Material* mtrl = btn->GetComponent<Sprite>(Sprite::_component_id)->GetMaterial();
	mtrl->_color = Vec4(0.0f, 0.5f, 5.0f, 0.1f);
	_world->AddChild(btn);

	//mtrl->Bind(Matrix4x4(1.0f));
	startX += size.x*0.5f;
	//startY += size.y+20;
	
	//sprite
	BaseNode* img = new BaseNode(Vec3(startX, startY, 0), size, 0);
	img->AddComponent(new Sprite("Assets/Textures/temp.png"));
	img->GetComponent<Sprite>()->GetMaterial()->_color = Vec4(1.0f, 1.0f, 1.0f, 1.5f);
	_world->AddChild(img);
	
	//startY += size.y + 20;
	startX += size.x*0.5f;

	Material* m = new MaterialDefault(r->GetShader(0), "Assets/Textures/temp.png");
	m->_color = Vec4(1.0f, 1.0f, 0.0f, 1.0f);
	BaseNode* img2 = new BaseNode(Vec3(startX, startY, 0), size, 0);
	img2->AddComponent(new Sprite(m));
	_world->AddChild(img2);
	//text
	//Text
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


MaterialTest::~MaterialTest() {
	std::cout << "deleting CollisionDetection\n";
	//delete _world;

}
//263 left
//262 right 
// 32 space 
#include "../../Math/CollisionDetection.h"
void MaterialTest::HandleKeyInputs(int key, int action, int mods) {

}

void MaterialTest::Update(float deltaTime) {
	Game::Update(deltaTime);

	Draw();



}
void MaterialTest::Draw() {
	//float zOffset
	//if Transparent
	//		translate by zOff
	//		zOff+=0.001f
	Matrix4x4 m = Matrix4x4::GetMatrix(Vec3(400, 400, -3), Vec3(100,100, 1), 0)  ;
	Matrix4x4 m1 = Matrix4x4::GetMatrix(Vec3(350, 350, -2), Vec3(100, 100, 1), 0);
	Matrix4x4 m2 = Matrix4x4::GetMatrix(Vec3(400, 350, -1), Vec3(100, 100, 1), 0);
	Renderer* r = Renderer::instance();
	const Texture* t = r->LoadTexture("Assets/Textures/default.png");
	const Texture* t1 = r->LoadTexture("Assets/Textures/pogcattile.png");
	const Texture* t2 = r->LoadTexture("Assets/Textures/temp.png");
	Shader* s = new Shader("Assets/Shaders/defaultNoTex.vert", "Assets/Shaders/defaultNoTex.frag");
	
	
	//Renderer::instance()->Draw(_world);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	auto children = _world->GetAllChildren();
	

	s->Activate();
	
	glUniformMatrix4fv(glGetUniformLocation(s->ID, "model"), 1, GL_TRUE, &m.buff[0]);
	glUniformMatrix4fv(glGetUniformLocation(s->ID, "proj"), 1, GL_TRUE, r->GetProjection()->buff);
	glUniform4f(glGetUniformLocation(s->ID, "color"), 0.250f, 0.340f, 0.20f ,1);
	
	
	r->GetVAO()->Bind();
	glEnable(GL_BLEND);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glUseProgram(0);

	s->Activate();

	glUniformMatrix4fv(glGetUniformLocation(s->ID, "model"), 1, GL_TRUE, &m1.buff[0]);
	glUniformMatrix4fv(glGetUniformLocation(s->ID, "proj"), 1, GL_TRUE, r->GetProjection()->buff);
	glUniform4f(glGetUniformLocation(s->ID, "color"), 0.250f, 0.60f, 0.20f, 0.10f);


	r->GetVAO()->Bind();
	glEnable(GL_BLEND);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glUseProgram(0);

	s->Activate();

	glUniformMatrix4fv(glGetUniformLocation(s->ID, "model"), 1, GL_TRUE, &m2.buff[0]);
	glUniformMatrix4fv(glGetUniformLocation(s->ID, "proj"), 1, GL_TRUE, r->GetProjection()->buff);
	glUniform4f(glGetUniformLocation(s->ID, "color"), 0.50f, 0.30f, 0.80f, 0.50f);


	r->GetVAO()->Bind();
	glEnable(GL_BLEND);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glUseProgram(0);

	glfwSwapBuffers(Renderer::instance()->GetWindow());
	glfwPollEvents();//<------------- THIS SHOULD BE IN MAIN ?
	delete s;
}
void MaterialTest::Play(const bool on) {

}

