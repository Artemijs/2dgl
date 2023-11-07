#include "CollisionTesMain.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Sprite.h"
#include "../../Math/BoxBounds.h"
#include "../../Math/SphereBounds.h"
//
#include "../../UI/Button.h"
#include "../../Graphics/Materials/DiffuseMaterial.h"


//												PHYSICS TEST GAME





PhysicsTest::PhysicsTest() :Game() {

	_myNode = new BaseNode(Vec3(450, 400, 0), Vec3(50, 50, 1), 0);
	Transform* t = &_myNode->GetTransform();
	//t->_position = Vec3();
	PhysicsObject* body = new PhysicsObject(t);
	//body->SetPhysData(Vec3(), Vec3(100, 0, 0));
	_myNode->AddComponent<PhysicsObject>(body);
	Sprite* s = new Sprite("Assets/Textures/Circle.png");
	//s->GetMaterial()
	_myNode->AddComponent(s);
	Bounds* bBox = new SphereBounds(_myNode, 25);

	//bBox->_solid = false;		
	_myNode->AddComponent(bBox);
	_world->AddChild(_myNode);

	_play = false;

	

}
/// <summary>
/// Im writing this down.
/// "Im not." 
/// Who said im not?
/// "I said im not. Dont worry im not actually wirting this down."
/// Who said my name in russian?
/// "I dont think anybody said it."
/// Someone said it. Who is imagining a naked old man with a pedo smile?
/// "Artysha ti znajesh shto projeshodit. Ne nado mne tut."
/// Who said that?
/// "I said that."
/// What do you mean by that? 
/// "You know whats happening."
/// "Why, again is someone imagining his sisters husband now?"
/// "Im just remembering what happened here."
/// Fuck off and stop doing that. Stop imagining her husband. Your abuse has been recorded.
/// "Thats hardly... abuse."
/// 
/// "Tusichu let ja evo one videl."
/// Who are you bullying now?
/// 
/// 
/// "A mi molchim"
/// Who are you and why are you satying quiet?
/// "WE dont want to get involved."
/// Why did you say that in russian?
/// "We werent informed."
/// If you werent informed than how do you know to say that and what that means?
/// "I wont do it again sir."
/// "Choto ti menja... opjatj..."
/// Did you not just say that you will not speak russian here?
/// "I can confidentally say tat that wasnt me."
/// "Znakomaja situacija."
/// Why did you try to trigger me?
/// "Fuck i didnt mean to say that." 
/// Well you fucking did. Speaking russian here is considered knwing and willing abuse.
/// "I was not informed."
/// Really? He didnt spend 2 years telling you not to do that already?
/// </summary>

PhysicsTest::~PhysicsTest() {
	std::cout << "deleting CollisionDetection\n";
	delete _world;

}
//263 left
//262 right 
// 32 space 
#include "../../Math/CollisionDetection.h"
#include "../../UI/Text.h"
void PhysicsTest::HandleKeyInputs(int key, int action, int mods) {
	//if (action == 2) return;
	//

	if (action == 0) {
		std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
		switch (key)
		{
		case 32:
			Play(!_play);
			break;
		case 49:
			break;
			//left
		default:
			break;
		}

	}
	else if (action == 2) { //m held
		switch (key)
		{
		case 87:
			MoveMyNode(0);
			break;
		case 65:
			MoveMyNode(1);
			break;
		case 83:
			MoveMyNode(2);
			break;
		case 68:
			MoveMyNode(3);
			break;
		default:
			break;
		}
	}
}

void PhysicsTest::MoveMyNode(const unsigned int dir) {
	Vec3 mpos = _myNode->GetTransform()._position;
	Vec3 movDir = Vec3();
	const float speed = 10;

	if (dir == 0) {
		movDir.y = 1;
	}
	else if (dir == 1) {
		movDir.x = -1;
	}
	else if (dir == 2) {
		movDir.y = -1;
	}
	else {
		movDir.x = 1;
	}


	_myNode->SetPosition(mpos + movDir * speed);
}
void PhysicsTest::Update(float deltaTime) {
		
	if (_play) return;
		//add force in the direction from the mouse to the object
	if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_DOWN) {
		printf("MOUSE DOWN \n");
		PhysicsObject* body = _myNode->GetComponent<PhysicsObject>();
		Vec3 dir = (_myNode->GetTransform()._position - _mouse->GetMousePosV3());
		dir.Normalize();
		body->AddForce(dir*10000.0f);
	}	
	if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_HELD) {
		printf("MOUSE HELD\n");

	}	
	if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_UP) {
		printf("MOUSE KEY UP \n");

	}	
	Vec2 mpos = Game::GetMouse()->GetPosition();
		
	Game::Update(deltaTime);
}	

void PhysicsTest::Play(const bool on) {
	_play = on;
}







//void Add(float a, float b) {}
//#define + Add
void CollisionTestMain::CreatePlayerCube(const bool physics) {

	_myNode = new BaseNode(Vec3(100, 100, 0), Vec3(rRad * 2, rRad * 2, 1), 0);
	
	if (physics) {
		PhysicsObject* body = new PhysicsObject(&_myNode->GetTransform());
		body->SetMass(1);
		body->SetCoefRestitution(1.0f);
		_myNode->AddComponent<PhysicsObject>(body);
	}
	
	Sprite* s = new Sprite();
	s->GetMaterial()->_color = Vec4(0.7f, 0.5f, 0.3f, 1.0f);
	
	Bounds* bBox = new BoxBounds(_myNode);

	_myNode->AddComponent(s);
	_myNode->AddComponent(bBox);
	_world->AddChild(_myNode);

}


void CollisionTestMain::CreatePlayerCircle(const bool physics) {
	_myNode = new BaseNode(Vec3(100, 100, 0), Vec3(rRad , rRad , 1), 0);

	if (physics) {
		PhysicsObject* body = new PhysicsObject(&_myNode->GetTransform());
		body->SetMass(1);
		body->SetCoefRestitution(0.05f);
		_myNode->AddComponent<PhysicsObject>(body);
	}

	Sprite* s = new Sprite("Assets/Textures/Circle.png");
	s->GetMaterial()->_color = Vec4(0.7f, 0.5f, 0.3f, 1.0f);

	Bounds* bBox = new SphereBounds(_myNode, rRad*0.5f);

	_myNode->AddComponent(s);
	_myNode->AddComponent(bBox);
	_world->AddChild(_myNode);
}


void CollisionTestMain::CreateCIRCLES(const unsigned int count) {
	
	unsigned int maxNodes = 10;
	_otherNodes = new BaseNode[maxNodes];
	int windowW = Renderer::instance()->GetWindowSize().x;
	int windowH = Renderer::instance()->GetWindowSize().y;

	for (int i = 0; i < count; i++) {
		float randx = rand() % windowW;
		float randy = rand() % windowW;

		Vec3 randPos = Vec3(randx, randy, 0);
		//int rRad = 25;
		BaseNode* b = new BaseNode(randPos, Vec3(rRad, rRad, 1), 0);
		PhysicsObject* body = new PhysicsObject(&b->GetTransform());
		body->SetPhysData(1);
		body->SetCoefRestitution(0.05f);
		b->AddComponent(body);
		b->AddComponent(new Sprite("Assets/Textures/Circle.png"));

		BaseNode* txtNode = new BaseNode(Vec3(0, 0, 0), Vec3(1, 1, 1), 0);
		b->AddChild(txtNode);
		txtNode->SetInheritTransform(1, false);
		txtNode->AddComponent(new Text(std::to_string((int)(body->GetMass())), txtNode, 12));

		Bounds* bBox = new SphereBounds(b, rRad * 0.5f);

		//bBox->_solid = false;					
		b->AddComponent(bBox);

		_otherNodes->AddChild(b);
		_world->AddChild(b);
	}

}


void CollisionTestMain::CreateSquares(const unsigned int count) {
	
	unsigned int maxNodes = 10;
	_otherNodes = new BaseNode[maxNodes];
	int windowW = Renderer::instance()->GetWindowSize().x;
	int windowH = Renderer::instance()->GetWindowSize().y;

	for (int i = 0; i < count; i++) {
		float randx = rand() % windowW;
		float randy = rand() % windowW;

		Vec3 randPos = Vec3(randx, randy, 0);

		BaseNode* b = new BaseNode(randPos, Vec3(rRad, rRad, 1), 0);
		PhysicsObject* body = new PhysicsObject(&b->GetTransform());
		body->SetPhysData(1);
		body->SetCoefRestitution(0.5f);
		BaseNode* txtNode = new BaseNode(Vec3(0, 0, 0), Vec3(1, 1, 1), 0);
		b->AddChild(txtNode);
		txtNode->SetInheritTransform(1, false);
		txtNode->AddComponent(new Text(std::to_string((int)(body->GetMass())), txtNode, 12));

		b->AddComponent(body);
		b->AddComponent(new Sprite("Assets/Textures/default.png"));
		Bounds* bBox = new BoxBounds(b);

		b->AddComponent(bBox);

		_otherNodes->AddChild(b);
		_world->AddChild(b);
	}

}


void CollisionTestMain::CreateWall(const float& w, const float& h) {
	
	BaseNode* wall = new BaseNode(Vec3(400, 400, 0), Vec3(w, h, 1), 0);
	Sprite* wallSprt = new Sprite();
	PhysicsObject* wallBod = new PhysicsObject(&wall->GetTransform());
	Bounds* wallBox = new BoxBounds(wall);
	
	wallBod->SetPhysData(500);
	wallBod->SetCoefRestitution(0.05f);

	wall->AddComponent(wallSprt);
	wall->AddComponent(wallBod);
	wall->AddComponent(wallBox);
	_world->AddChild(wall);

}

/// <summary>
/// THE ERROR ONLY HAPPENS WITH circles THAT ARE NOT the first child of the world
/// </summary>
CollisionTestMain::CollisionTestMain():Game() {
	
	rRad = 30;
	_play = false;
	_angVel = 0;
	_ang = 0;
	//i have to properly update the collision Bounds to the world
	//CreatePlayerCube(false);
	//CreateWall(rRad, rRad);
	//CreatePlayerCircle(false);
	//CreateWall(50, 400);
	//CreatePlayerCube(false);
	CreatePlayerCircle(true);
	CreateSquares(5);
	CreateCIRCLES(10);
	CreateSquares(5);
	

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
	//if (action == 2) return;
	//
	
	if (action == 0) {
		std::cout << " key event called from tower defense " << "aaction " << action << " key " << key << " mods " << mods << "\n";
		switch (key)
		{
		case 32:
			Play(!_play);
			break;
		case 49:
			break;
			//left
		default:
			break;
		}
		
	}
	else if (action == 2) { //m held
		switch (key)
		{
			case 87:
				MoveMyNode(0);
				break;
			case 65:
				MoveMyNode(1);
				break;
			case 83:
				MoveMyNode(2);
				break;
			case 68:
				MoveMyNode(3);
				break;
			default:
				break;
			}
	}
}

void CollisionTestMain::MoveMyNode(const unsigned int dir) {
	
	Vec3 movDir = Vec3();
	const float speed = 500;

	if (Keyboard::GetKey('w')->state == KeyState::KEY_HELD) {
		//printf("W PRESSED\n");
		movDir.y = 1;
	}
	if (Keyboard::GetKey('a')->state == KeyState::KEY_HELD) {
		//printf("A PRESSED\n");
		movDir.x = -1;
	}
	if (Keyboard::GetKey('s')->state == KeyState::KEY_HELD) {
		//printf("S PRESSED\n");
		movDir.y = -1;
	}
	if(Keyboard::GetKey('d')->state == KeyState::KEY_HELD){
		//printf("D PRESSED\n");
		movDir.x = 1;
	}
	PhysicsObject* body = _myNode->GetComponent<PhysicsObject>();
	if(body != NULL)
		body->AddForce(movDir * speed);
	//_myNode->SetPosition(mpos + movDir * speed);
	
}
void CollisionTestMain::Update(float deltaTime) {
	if (_play) return;
	Game::Update(deltaTime);
	//if (!_play) return;
	double xpos, ypos;
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &xpos, &ypos);

	/*_ang += Utility::Deg2Rad(1.0f);

	auto children = _world->GetAllChildren(); 
	for (int i = 4; i < children->size(); i++) {
		//Vec3 v = children->at(i)->GetTransform()._angle;
		children->at(i)->SetAngle(Vec3(0, _ang, 0));
	}*/



	ypos = Renderer::instance()->GetWindowSize().y - ypos;
	if (_mouse->GetMouseKey(0)->_state == MouseKeyState::KEY_HELD) {
		_myNode->SetPosition(Vec3(xpos, ypos, 0));
	}
	MoveMyNode(0);
	WrapWorld();
}

void CollisionTestMain::Play(const bool on) {
	_play = on;
}


void CollisionTestMain::WrapWorld() {
	Vec2 windowSize = Renderer::instance()->GetWindowSize();

	auto allGameObjects = _world->GetAllChildren();
	for (int i = 0; i < allGameObjects->size(); i++) {
		auto gameObject = allGameObjects->at(i);
		Transform goTransform = gameObject->GetTransform();
		if (goTransform._position.x < -goTransform._scale.x) {
			//move the game object to the edge of the right side of the screen
			Vec3 newPosition = goTransform._position;
			newPosition.x = windowSize.x + goTransform._scale.x;
			gameObject->SetPosition(newPosition);
		}
		else if (goTransform._position.x > windowSize.x + goTransform._scale.x){
			//move the object to the left of the left edge of the screen
			Vec3 newPosition = goTransform._position;
			newPosition.x = -goTransform._scale.x;
			gameObject->SetPosition(newPosition);
		}
		if (goTransform._position.y > windowSize.y +goTransform._scale.y) {
			//move the object to the top of the screen
			Vec3 newPosition = goTransform._position;
			newPosition.y = -goTransform._scale.y;
			gameObject->SetPosition(newPosition);
		}
		else if (goTransform._position.y < -goTransform._scale.y) {
			//.move the object to the bottom of the screen
			Vec3 newPosition = goTransform._position;
			newPosition.y = windowSize.y + goTransform._scale.y;
			gameObject->SetPosition(newPosition);
		}


	}
	/*auto allChildren = _world->GetAllChildren();
	for (int i = 0; i < allChildren->size(); i++) {
		auto child = allChildren->at(i);
		Transform childTransform = child->GetTransform();
		if(child<
	}*/
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



#include "../../Game/Mesh/MeshLoader.h"
/// <summary>
/// CANNOT SET MATERIAL
/// </summary>
/// 
MaterialTest::MaterialTest() :Game() {
	Renderer* r = Renderer::instance();
	//button
	float startX = 200;
	float startY = 100;
	Vec3 size = Vec3(200, 75, 1);
	
	btn = new Button("Hi!", Vec3(startX, startY, 0), size, 0);			
	BaseMaterial* mtrl = btn->GetComponent<Sprite>(Sprite::_component_id)->GetMaterial();
	//mtrl->_color = Vec4(0.0f, 0.5f, 5.0f, 0.1f);
	_world->AddChild(btn);


	
	//mtrl->Bind(Matrix4x4(1.0f));
	startX += size.x;
	//startY += size.y+20;
	
	//											SPRITE WITH IMAGE, MATERIAL_UI_SPRITE
	BaseNode* img = new BaseNode(Vec3(startX, startY, 0), size, 0);
	img->AddComponent(new Sprite("Assets/Textures/temp.png"));
	//img->GetComponent<Sprite>()->GetMaterial()->_color = Vec4(1.0f, 1.0f, 1.0f, 1.5f);
	_world->AddChild(img);
	
	//startY += size.y + 20;


	startX += size.x*0.5f;
	//											PLANE WITH DEFAULT DIFFUSE SHADER
	/*Material* m = new DiffuseMaterial();
	m->_color = Vec4(1.0f, 1.0f, 0.0f, 1.0f);
	BaseNode* img2 = new BaseNode(Vec3(startX, startY, 0), size, 0);
	img2->AddComponent(new Sprite(m));
	_world->AddChild(img2);
	*/

	//text
	//Text
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//(*Renderer::instance()->GetProjection()) = Matrix4x4::Perspective(Utility::Deg2Rad(90), r->GetWindowSize().x / r->GetWindowSize().y, 0.1f, 1000.0f);
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

	//Draw();



}
#include "../../Graphics/Materials/DiffuseMaterial.h"
void MaterialTest::TestMaterials() {
	
	Renderer* r = Renderer::instance();
	Matrix4x4 translation = Matrix4x4::TranslationMatrix(Vec3(0, 100, 0));

	


	//											DIFFUSE MATERIAL
	Matrix4x4 m1 = Matrix4x4::GetMatrix(Vec3(200, 150, -1), Vec3(100, 100, 1), Vec3());
	BaseMaterial* diffuseMat = new BaseMaterial();
	diffuseMat->_color = Vec4(0.5f, 0.6, 0.1f, 1);
	diffuseMat->Bind(&m1);	
	r->GetVAO()->Bind();	
						
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);


	//											MATERIAL
	m1 =  translation * m1;
	BaseMaterial* mat = new Material();
	mat->Bind(&m1);
	r->GetVAO()->Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);


	//											MATERIAL BUTTON
	m1 = translation * m1;
	BaseMaterial* btnMat= new MaterialUiButton();
	btnMat->Bind(&m1);
	r->GetVAO()->Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);


	//											MATERIAL SPRITE
	m1 = translation * m1;
	BaseMaterial* spriteMat = new MaterialUiSprite();
	spriteMat->Bind(&m1);
	r->GetVAO()->Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);


	//											BUTTON
	//btn->GetGraphic()->Draw(btn->GetModelMatrix());

	const Matrix4x4* btnm = btn->GetModelMatrix();
	BaseMaterial* btnMat1 = btn->GetGraphic()->GetMaterial();
	//btnMat1->_color = Vec4(0.5f, 0.6, 0.1f, 1);
	btnMat1->Bind(btnm);
	r->GetVAO()->Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);



	delete diffuseMat;
	delete mat;
	delete btnMat;
	delete spriteMat;

}
void MaterialTest::Draw() {
	//float zOffset
	//if Transparent
	//		translate by zOff
	//		zOff+=0.001f
	Matrix4x4 m = Matrix4x4::GetMatrix(Vec3(400, 400, -3), Vec3(100,100, 1), Vec3())  ;
	Matrix4x4 m1 = Matrix4x4::GetMatrix(Vec3(350, 350, -2), Vec3(100, 100, 1), Vec3());
	Matrix4x4 m2 = Matrix4x4::GetMatrix(Vec3(400, 350, -1), Vec3(100, 100, 1), Vec3());
	Matrix4x4 m3 = Matrix4x4::GetMatrix(Vec3(200, 150, -1), Vec3(100, 100, 1), Vec3());
	Renderer* r = Renderer::instance();
	const Texture* t = r->LoadTexture("tex0", "Assets/Textures/default.png");
	const Texture* t1 = r->LoadTexture("tex0", "Assets/Textures/pogcattile.png");
	const Texture* t2 = r->LoadTexture("tex0", "Assets/Textures/temp.png");
	Shader* s = new Shader("Assets/Shaders/defaultNoTex.vert", "Assets/Shaders/defaultNoTex.frag");
	//Shader* s2 = Renderer::instance()->GetShader(1);
	
	
	//Renderer::instance()->Draw(_world);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	auto children = _world->GetAllChildren();
	
	TestMaterials();



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

