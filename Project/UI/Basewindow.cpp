#include "Basewindow.h"
#include "../Math/BoxBounds.h"
#include "../Input/MouseEventController.h"
BaseWindow::BaseWindow():Sprite(), MouseEvent(new BoxBounds(), this) {

}
//path to the source of the background image
BaseWindow::BaseWindow(const char* path, Vec3 pos, Vec3 size, float ang) : Sprite(path, pos, size, ang), MouseEvent(new BoxBounds(), this) {

}
//uses default image as background
BaseWindow::BaseWindow(Vec3 pos, Vec3 size, float ang): Sprite("Assets/Textures/default_win.png", pos, size, ang), MouseEvent(new BoxBounds(), this) {

}

void BaseWindow::Update(float deltaTime) {
	if (!_dragging)return;
	std::cout << "update called \n";
	Vec2 newMouse = (*MouseEventController::GetMousePosition());
	Vec2 offset = newMouse - _prevMouse;
	if(offset.x !=0 || offset.y != 0)
		std::cout << offset.x << " " << offset.y << "\n";
	_transform._position.x += offset.x;
	_transform._position.y += offset.y;

	_prevMouse = newMouse;
}

void BaseWindow::OnMouseEnter(const Vec2* mPos) {
}
void BaseWindow::OnMouseLeave(const Vec2* mPos) {
}
//these need to be rewritten 
void BaseWindow::OnPressed(const Vec2* mpos) {
	_prevMouse =  (*MouseEventController::GetMousePosition());
	_dragging = true;
}
void BaseWindow::OnReleased(const Vec2* mpos) {
	_dragging = false;
}
void BaseWindow::OnClick(const Vec2* mPos) {

}

void BaseWindow::OnDoubleClick(const Vec2* mPos) {
}
void BaseWindow::OnHover(const Vec2* mPos) {
}
void BaseWindow::OnEndHover(const Vec2* mPos) {

}
