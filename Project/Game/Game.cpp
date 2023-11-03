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
#include "../Util/MemoryManager.h"
Mouse* Game::_mouse = new Mouse();
PhysicsWorld* Game::_physWorld = new PhysicsWorld();
BaseNode* Game::_world = new RenderNode(Vec3(0, 0, -10), Renderer::instance()->WindowSizeVec3(), 0);

Game::Game() {
	Keyboard::Init();
	Text::Init();	
	_switch = false;
	//_world->AddChild(new Button("LOL", Vec3(400, 400, 0), Vec3(100, 50, 1), 0));
	_ang = 0.0f;
	_isRunning = true;
	//_physWorld = new PhysicsWorld();
	
}
Game::~Game() {
	std::cout << "deleting game\n";
	Keyboard::Delete();

	delete _physWorld;

	delete Renderer::instance();

	delete _world;

	MouseEventHandler::Delete();
	delete _mouse;
	CollisionHandler::Delete();

	
	MemoryManager::ClearMemory();
	MemoryManager::Clean();
}
//remove all ui code
//add UpdateModelMatrix(parentPos, parentScale, parentRot)
//make every graphic object inherit from element

void Game::Test() {
	printf("HELLO FROM BLACK mAGIC PORTAL\n");
}

void Game::Update(float deltaTime) {
	//UPDATE KEYBOARD
	Keyboard::Update(deltaTime);

	//MOUSE EVENTS
	_mouse->Update(deltaTime);  

	//PHYSICS 
	_physWorld->Step(deltaTime);
	
	//UPDATE GAME OBJECTS
	_world->TryUpdate(deltaTime);

	//CREATE THE MODEL MATRIX FOR EVERY OBJECT
	_world->MakeModelMatrix(Matrix4x4(1), Matrix4x4(1), Matrix4x4(1));
	
	//TRANSLATE COLLISION VOUNDS BYY THEIR BASE NODES MODEL MATRIX
	CollisionHandler::TranslateByModel();
	
	
	_ang += 5 * deltaTime;

	//RESOLVE COLLISIONS 
	CollisionHandler::Update(deltaTime);
	
	//HANDLE UI MOUSE COLLISION AND EVENTS
	Vec3 mouseInWorld = Renderer::instance()->GetCamera()->GetViewMatrix()->Inverse() * _mouse->GetMousePosV3();

	MouseEventHandler::HandleMouseMoving(mouseInWorld, deltaTime);
	MouseEventHandler::Update(deltaTime);
}

void Game::Draw() {
	//return; //WHO DID THIS?

	//Renderer::instance()->DrawNodes(_world, _world);
	if (Keyboard::GetKey(' ')->state == KeyState::KEY_DOWN) {
		_switch = !_switch;
	}
	
	//Renderer::instance()->Draw(_world);
	if (!_switch) {
		Renderer::instance()->Draw(_world);
	}
	else {
		//v1_5::Renderer::instance()->DrawNodes(_world, _world);
		Renderer::instance()->DrawNodes(_world, _world);
	}
	glfwSwapBuffers(Renderer::instance()->GetWindow());
	glfwPollEvents();//<------------- THIS SHOULD BE IN MAIN ?
	
}


bool Game::IsRunning() { return _isRunning; }
PhysicsWorld* Game::GetPhyscisWorld() {
	return _physWorld;
}
Mouse* Game::GetMouse() {
	return _mouse;
}