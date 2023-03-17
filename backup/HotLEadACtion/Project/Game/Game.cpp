#include "Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/MouseEventController.h"
#include <iostream>
Game::Game() {
	Text::Init();
	_isRunning = true;
	/*_sprt = new Sprite("Assets/Textures/default.png", Vec3(100, 100, 0), Vec3(25, 25, 1), 0);
	_animsprt = new AnimatedSprite("Assets/Textures/snowball.png", Vec3(200, 100, -1), Vec3(50, 50, 1), 0);
	_animsprt->SetAnimationData(0, 5, 4, 4, 0.15f, true);
	_text = new Text(Vec3(400, 400, -1), 0, 10, "Hello world!");*/
	s = new UIsprite("Assets/Textures/default.png", Vec3(100, 400, -10), Vec3(50, 50, 1), 45);
	s1 = new UIsprite("Assets/Textures/default.png", Vec3(50, 0, 0), Vec3(50, 50, 1), 45);
	_slider = new UISlider(Vec3(400,400,-1), Vec3(15,300, 1), 0);
	_b1 = new Button(".", Vec3(100, 400, 0), Vec3(25, 25, 1), 0);
	/*SpriteData rect = Graphic::MakeSPD(Vec3(10, 10, -2), Vec2(10, 400), 0);
	_slider = new UISlider(rect);
	s1 = new UIsprite("Assets/Textures/sliderPinDefault.png", Graphic::MakeSPD(Vec3(-100, 100, -6), Vec2(50, 50), 0));
	rect._size = Vec2(50, 25);
	rect._position = Vec3(400, 400, -13);
	_b1 = new Button("btn1", rect);
	rect._position = Vec3(410, 400, -14);
	_b2 = new Button("btn2", rect);
	*/

	/*sp = new Sprite("Assets/Textures/Temp.png", Graphic::MakeSPD(Vec3(0, 0, 0), Vec2(100, 100), 0));
	_uias = new UIAnimatedSprite("Assets/Textures/snowball.png", Graphic::MakeSPD(Vec3(100, 100, 0), Vec2(100, 100), 0));
	_uias->SetAnimationData(0, 5, 4, 4, 0, true);
	_txt = new UIText(Vec3(0, -100, 0), 0, 10, "HI!");*/
	x = 0;
	s->AddChild(s1);
	//s1->MakeModelMatrix();
	//s->AddChild(_slider);
	//_slider->AddChild(s1);
	//s->AddChild(_b1);
	//s->AddChild(_b2);

}
Game::~Game() {
	
	delete Renderer::instance();
	delete s;
	delete s1;
	delete _slider;
	delete _b1;
	/*
	delete _slider;
	delete _b1;
	delete _b2;*/

	MouseEventController::Delete();
}
//remove all ui code
//add UpdateModelMatrix(parentPos, parentScale, parentRot)
//make every graphic object inherit from element


void Game::Update(float deltaTime) {
	x += 0.01f * deltaTime;
	double xpos, ypos;
	s->SetPosition(s->GetPosition() + Vec3(0, x, 0));
	//_slider->Up
	//_animsprt->Update(deltaTime);


	//PHYSICS 
	//- update all model matrices( parentTransform, parentScale, parentRotation)
		
		
	//MOUSE EVENTS
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &xpos, &ypos);
	ypos = Renderer::instance()->GetWindowSize().y - ypos;
	MouseEventController::HandleMouseMoving(Vec2(xpos, ypos), deltaTime);
	MouseEventController::Update(deltaTime);

	//KEYBOARD EVENTS


	
	
}
void Game::Draw() {
	//s->UpdateTransform(Matrix4x4(1));
	Vec3 p1 = s->GetPosition();
	std::cout << "p1 x :" << p1.x << " y: " << p1.y << " z : " << p1.z << "\n";
	Vec3 p2 = s1->GetPosition();
	std::cout << "p2 x :" << p2.x << " y: " << p2.y << " z : " << p2.z << "\n";
	Renderer::instance()->Draw();
}


void Game::HandleKeyInputs(int key, int action, int mods) {
	std::cout << " key event called \n";
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
