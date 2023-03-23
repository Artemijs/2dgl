#include "Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/MouseEventController.h"
#include <iostream>
Game::Game() {
	MouseEventController::Init();
	Text::Init();
	_isRunning = true;

	_world = new BaseObject(Vec3(0, 0, -10), Vec3(1, 1, 1), Vec3(0,0,0));

	MouseEventController::Init(_world);
}
Game::~Game() {
	std::cout << "deleting game\n";
	delete _world;
	delete Renderer::instance();
	MouseEventController::Delete();
}
//remove all ui code
//add UpdateModelMatrix(parentPos, parentScale, parentRot)
//make every graphic object inherit from element


void Game::Update(float deltaTime) {
	//translate children 
	_world->MakeModelMatrix(Matrix4x4(1), Matrix4x4(1), Matrix4x4(1));
	_world->TryUpdate(deltaTime);
	
	
	double xpos, ypos;

	//PHYSICS 
	//- update all model matrices( parentTransform, parentScale, parentRotation)
		
		
	//MOUSE EVENTS
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &xpos, &ypos);
	ypos = Renderer::instance()->GetWindowSize().y - ypos;
	MouseEventController::HandleMouseMoving(Vec2(xpos, ypos), deltaTime);
	MouseEventController::Update(deltaTime);

	//KEYBOARD EVENTS
	//std::cout << "game update\n";

	
	
}
void Game::Draw() {
	Renderer::instance()->Draw();
}


void Game::HandleKeyInputs(int key, int action, int mods) {
	if (action == GLFW_REPEAT) return;
	std::cout << " key event called "<<"aaction "<<action<<" key "<<key<<" mods "<<mods<<"\n";
	if (action == GLFW_PRESS) {
		
	}
	else if (action == GLFW_RELEASE) {
		
	}
}
void Game::HandleMouseInputs(int btn, int action) {
	std::cout << "btn event called \n";
	if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
		MouseEventController::HandleMouseClick(true);
	else if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		MouseEventController::HandleMouseClick(false);
	}
}
bool Game::IsRunning() { return _isRunning; }
