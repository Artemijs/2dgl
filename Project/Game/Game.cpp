#include "Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Sprite.h"
#include "../Input/MouseEventHandler.h"
//#include "../UI/RenderNode.h"
#include <iostream>
#include "../Math/BoxBounds.h"
#include "FBOComponent.h"
#include "RenderNode.h"
#include "../UI/Button.h"
#include <typeinfo>
#include "../UI/Text.h"
BaseNode* Game::_world = new RenderNode(Vec3(0, 0, -10), Renderer::instance()->WindowSizeVec3(), 0);
Graphic* Game::_testG = new Sprite("./Assets/Textures/default.png");
Game::Game() {
	_arg = 0;
	Text::Init();
	_switch = false;
	m = new MouseEvent();
	
	_isRunning = true;
	
	_world->AddChild(new Button("Start", Vec3(400, 400, 0), Vec3(100, 50, 1), 0));

	BaseNode* bn = new BaseNode(Vec3(400, 400, 0), Vec3(1, 1, 1), 0);
	_world->AddChild(bn);
	Text* t = new Text("TEST", bn, 12);
	//Text* t = new Text("Hello World!", 20, 12);
	bn->AddComponent<Text>(t);
	
	
	//_world->AddChild(new BaseNode(Vec3(400, 400, -10), Vec3(200, 100, 1), 0));
	//_world->GetChild(1)->AddComponent<Text>(new Text("HELLOHELLOHELLO", _world->GetChild(1), 12,5));
}
Game::~Game() {
	std::cout << "deleting game\n";
	//delete _world;
	delete Renderer::instance();
	//delete _testG;
	delete _world;
	delete m;
	delete _testG;
	MouseEventHandler::Delete();
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
	_arg += 0.01f;

	//PHYSICS 
	//- update all model matrices( parentTransform, parentScale, parentRotation)
		
		
	//MOUSE EVENTS
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &xpos, &ypos);
	
	ypos = Renderer::instance()->GetWindowSize().y - ypos;
	_world->GetChild(0)->SetPosition(Vec3(xpos, ypos, 0));
	_world->GetChild(0)->SetAngle(Vec3(0,_arg, 0));
	MouseEventHandler::HandleMouseMoving(Vec3(xpos, ypos, 0), deltaTime);
	MouseEventHandler::Update(deltaTime);

	//KEYBOARD EVENTS
	//std::cout << "game update\n";

	
	
}
void Game::Draw() {
	
	Renderer::instance()->DrawNodes(_world, _world);
	/*if (!_switch) {
		Renderer::instance()->Draw(_world);
	}
	else {
		//v1_5::Renderer::instance()->DrawNodes(_world, _world);
		Renderer::instance()->DrawNodes(_world, _world);
	}*/
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
	//std::cout << "btn event called \n";
	//m->OnPress();
	if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
		MouseEventHandler::HandleMouseClick(true);
	else if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		MouseEventHandler::HandleMouseClick(false);
	}
}
bool Game::IsRunning() { return _isRunning; }
