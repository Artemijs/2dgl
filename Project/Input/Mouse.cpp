#include "Mouse.h"
#include "../Graphics/Renderer.h"
#include "../Input/MouseEventHandler.h"



Mouse::Mouse() {
	_hidden = false;
}


Mouse::~Mouse() {
	
}


void Mouse::Update(const float deltaTime) {

	double x, y;
	glfwGetCursorPos(Renderer::instance()->GetWindow(), &x, &y);

	y = Renderer::instance()->GetWindowSize().y - y;
	_position.x = x;
	_position.y = y;

	Renderer::instance()->GetCamera()->MouseMove();

	MouseEventHandler::HandleMouseMoving(Vec3(x, y, 0), deltaTime);
	MouseEventHandler::Update(deltaTime);

}


void Mouse::SetCursorPos(const float& x, const float& y) {

	_position.x = x;
	_position.y = y;
	glfwSetCursorPos(Renderer::instance()->GetWindow(), x, y);

}


void Mouse::SetCursorPos(const Vec2& cursorpos) {

	_position = cursorpos;
	glfwSetCursorPos(Renderer::instance()->GetWindow(), _position.x, _position.y);

}


void Mouse::SetCursorHidden(const bool hidden) {

	_hidden = hidden;

	if (_hidden) {
		glfwSetInputMode(Renderer::instance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else {
		glfwSetInputMode(Renderer::instance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	}

}

/// <summary>
/// Handle mouse Button presses, MouseEvents and MouseCollision with UI
/// </summary>
/// <param name="btn"></param>
/// <param name="action"></param>
void Mouse::ButtonInput(const unsigned int btn, const unsigned int action) {
	
	if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		MouseEventHandler::HandleMouseClick(true);
		Renderer::instance()->GetCamera()->LockCursor(true);
	}
	else if (btn == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		MouseEventHandler::HandleMouseClick(false);
		Renderer::instance()->GetCamera()->LockCursor(false);
	}
	if (btn == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		Renderer::instance()->GetCamera()->_x = !Renderer::instance()->GetCamera()->_x;
	}

}


Vec2 Mouse::GetPosition() {return _position;}
bool Mouse::IsHidden() {return _hidden;}