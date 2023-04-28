#include "Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Sprite.h"

//#include "../UI/RenderNode.h"
#include <iostream>
#include "../Math/BoxBounds.h"
#include "FBOComponent.h"
#include "RenderNode.h"

BaseNode* Game::_world = new RenderNode(Vec3(0, 0, -10), Renderer::instance()->WindowSizeVec3(), 0);
Graphic* Game::_testG = new Sprite("./Assets/Textures/default.png");
Game::Game() {
	
	_switch = false;
	m = new MouseEvent<Game>(this);
	//m->SetCallBack(&Game::Test);
	
	//v1_5::Text::Init();
	_isRunning = true;
	_world->AddComponent(new FBOComponent(_world->GetTransform()._scale.x, _world->GetTransform()._scale.y));

	BaseNode* bn = new BaseNode(Vec3(100, 50, 0), Vec3(200, 100, 1), 0);
	bn->AddComponent(new Sprite("./Assets/Textures/default.png"));
	_world->AddChild(bn);
	
	BaseNode* rn = new RenderNode(Vec3(400, 400, 0), Vec3(400, 400, 1), 0);
	_world->AddChild(rn);
	
	BaseNode* bn1 = new BaseNode(Vec3(100, 50, 0), Vec3(200, 100, 1), 0);
	bn1->AddComponent(new Sprite("./Assets/Textures/default.png"));
	rn->AddChild(bn1);
	
	//MouseEventController::Init();
}
Game::~Game() {
	std::cout << "deleting game\n";
	//delete _world;
	delete Renderer::instance();
	//delete _testG;
	delete _world;
	delete m;
	delete _testG;
	//MouseEventController::Delete();
}
//remove all ui code
//add UpdateModelMatrix(parentPos, parentScale, parentRot)
//make every graphic object inherit from element

void Game::Test() {
	printf("HELLO FROM BLACK mAGIC PORTAL\n");
}
void Game::Update(float deltaTime) {
	//translate children 
	_world->MakeModelMatrix(Matrix4x4(1), Matrix4x4(1), Matrix4x4(1));
	//update the world
	_world->TryUpdate(deltaTime);
	//check collision
	
	double xpos, ypos;

	//PHYSICS 
	//- update all model matrices( parentTransform, parentScale, parentRotation)
		
		
	//MOUSE EVENTS
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &xpos, &ypos);
	ypos = Renderer::instance()->GetWindowSize().y - ypos;
	//MouseEventController::HandleMouseMoving(Vec2(xpos, ypos), deltaTime);
	//MouseEventController::Update(deltaTime);

	//KEYBOARD EVENTS
	//std::cout << "game update\n";

	
	
}
void Game::Draw() {
	//Renderer::instance()->Draw();
	/*glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);*/
	//Renderer::instance()->Draw(_world);
	
	
	if (_switch) {
		Renderer::instance()->Draw(_world);
	}
	else {
		//v1_5::Renderer::instance()->DrawNodes(_world, _world);
		Renderer::instance()->DrawNodes(_world, _world);
	}
	glfwSwapBuffers(Renderer::instance()->GetWindow());
	glfwPollEvents();//<------------- THIS SHOULD BE IN MAIN ?
	
}


void Game::HandleKeyInputs(int key, int action, int mods) {
	if (action == GLFW_REPEAT) return;
	std::cout << " key event called "<<"aaction "<<action<<" key "<<key<<" mods "<<mods<<"\n";
	if (action == GLFW_PRESS) {
		_switch = !_switch;
	
	}
	else if (action == GLFW_RELEASE) {
		
	}
}
void Game::HandleMouseInputs(int btn, int action) {
	std::cout << "btn event called \n";
	//m->OnPress();
	//if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
		//MouseEventController::HandleMouseClick(true);
	//else if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		//MouseEventController::HandleMouseClick(false);
	//}
}
bool Game::IsRunning() { return _isRunning; }
