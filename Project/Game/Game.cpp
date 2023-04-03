#include "Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/MouseEventController.h"
#include "../UI/RenderNode.h"
#include <iostream>

//BaseObject* Game::_world = new RenderNode(Vec3(0, 0, -10), Renderer::instance()->WindowSizeVec3(), 0);
BaseObject* Game::_world = NULL;
 Graphic* Game::_testG = new Sprite("./Assets/Textures/default.png", Vec3(400, 400, -10), Vec3(50, 50, 1), 0, NULL);
Game::Game() {
	_switch = false;
	_world = new RenderNode(Vec3(0, 0, -10), Renderer::instance()->WindowSizeVec3(), 0);
	//_world = new RenderNode(Vec3(0, 0, -10), Vec3(400, 400, 1), 0);
	Text::Init();
	_isRunning = true;
	//_world->AddChild(_testG);

	MouseEventController::Init();
}
Game::~Game() {
	std::cout << "deleting game\n";
	delete _world;
	delete Renderer::instance();
	delete _testG;
	MouseEventController::Delete();
}
//remove all ui code
//add UpdateModelMatrix(parentPos, parentScale, parentRot)
//make every graphic object inherit from element


void Game::Update(float deltaTime) {
	//translate children 
	Game::_world->MakeModelMatrix(Matrix4x4(1), Matrix4x4(1), Matrix4x4(1));
	Game:: _world->TryUpdate(deltaTime);
	
	
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
	//Renderer::instance()->Draw();
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if (_switch) {
		Renderer::instance()->Draw();
	}
	else {
		Renderer::instance()->DrawNodes(_world, _world);

		glfwSwapBuffers(Renderer::instance()->GetWindow());
		glfwPollEvents();//<------------- THIS SHOULD BE IN MAIN ?
	}
	
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
