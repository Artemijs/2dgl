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
#include "../Math/CollisionHandler.h"

BaseNode* Game::_world = new RenderNode(Vec3(0, 0, -10), Renderer::instance()->WindowSizeVec3(), 0);

Game::Game() {
	
	Text::Init();
	_switch = false;
	//_world->AddChild(new Button("LOL", Vec3(400, 400, 0), Vec3(100, 50, 1), 0));
	_ang = 0.0f;
	_isRunning = true;
	
}
Game::~Game() {
	std::cout << "deleting game\n";

	delete Renderer::instance();
	delete _world;
	MouseEventHandler::Delete();
	CollisionHandler::Delete();
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
	_ang += 5 * deltaTime;
	//_world->GetChild(0)->SetAngle(Vec3(0, _ang, 0));

	//PHYSICS 
	//- update all model matrices( parentTransform, parentScale, parentRotation)
	CollisionHandler::Update(deltaTime);
		
	//MOUSE EVENTS
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &xpos, &ypos);
	
	ypos = Renderer::instance()->GetWindowSize().y - ypos;
	MouseEventHandler::HandleMouseMoving(Vec3(xpos, ypos, 0), deltaTime);
	MouseEventHandler::Update(deltaTime);

	//KEYBOARD EVENTS
	//std::cout << "game update\n";

	
	
}
void Game::Draw() {
	//return; WHO DID THIS?

	Renderer::instance()->DrawNodes(_world, _world);
	//Renderer::instance()->Draw(_world);
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
