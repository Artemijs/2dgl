#include "Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/MouseEventController.h"
#include <iostream>
Game::Game() {
	Text::Init();
	_isRunning = true;

	_g = new Sprite("Textures/default.png", Graphic::MakeSPD(Vec3(100, 400, 0), Vec2(50, 100), 0));
	_as = new AnimatedSprite("Textures/snowball.png", Graphic::MakeSPD(Vec3(100, 500, 0), Vec2(100, 100), 0));
	_as->SetAnimationData(0, 3, 4, 4, 0.5f, true);
	_text = new Text(Vec3(400, 400, 0), 0, 10, "Hello World!", 5);
	x = 0;
	_b = new Button("press", Graphic::MakeSPD(Vec3(400, 400, 0), Vec2(75, 50), 0));
	_b = new Button("press1", Graphic::MakeSPD(Vec3(390, 400, -2), Vec2(75, 50), 0));
}
Game::~Game() {
	delete _g;
	delete Renderer::instance();
	delete _as;
	delete _text;
	delete _b;
	delete _b1;
	MouseEventController::Delete();
}
void Game::Update(float deltaTime) {
	_as->Update(deltaTime);
	x += (0.5) * deltaTime;
	Vec3 p = _text->GetRect()._position;
	p.x += x;
	//_text->SetPosition(p);
	_text->SetAngle(x);

	double xpos, ypos;
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &xpos, &ypos);
	ypos = Renderer::instance()->GetWindowSize().y - ypos;
	MouseEventController::HandleMouseMoving(Vec2(xpos, ypos), deltaTime);
	MouseEventController::Update(deltaTime);
	
}
void Game::Draw() {
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
