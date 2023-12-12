#include "Graphics/Camera.h"
#include "Graphics/Renderer.h"
#include "Game/Game.h"
Camera::Camera() {
	_up = Vec3(0.0f, 1.0f, 0.0f);
	_orientation = Vec3(0.0f, 0.0f, 1.0f);
	_sensitivity = 1.1f;
	_firstClick = true;
	_x = false;
	_cursorLocked = false;
	_position = Vec3();
	_mouse = Game::GetMouse();
	CalculateViewMatrix();
}

Camera::Camera(unsigned int height, unsigned int width, Vec3 position) : _width(width), _height(height), _position(position){
	_up = Vec3(0.0f, 1.0f, 0.0f);
	_orientation = Vec3(0.0f, 0.0f, 1.0f);		
	_sensitivity = 1.1f;			
	_firstClick = true;					
	_cursorLocked = false;			
	_x = false;			
	_mouse = Game::GetMouse();
	CalculateViewMatrix();
}

void Camera::CalculateViewMatrix() {
	
	Vec3 Z = _orientation;
	Vec3 X = Vec3::Cross(_up, Z);
	X.Normalize();
	Vec3 Y = Vec3::Cross(Z, X);
	Y.Normalize();
	_viewMatrix = Matrix4x4::GetCameraMatrix(X, Y, Z, _position);
	


}
Matrix4x4* Camera::GetViewMatrix() {
	return &_viewMatrix;
}
Vec3 Camera::GetPosition() {
	return _position;
}

void Camera::SetPosition(Vec3 pos) {
	_position = pos;
}

Vec3 Camera::GetOrientation() {
	return _orientation;
}

void Camera::SetOrientation(Vec3 dir) {
	_orientation = dir;
}


void Camera::MouseMove() {

	if (_cursorLocked) {
		Vec2 pos = _mouse->GetPosition();
		if (_firstClick) {
			_mouse->SetCursorPos((_width / 2), (_height / 2));
			_firstClick = false;
			return;
		}

		float rotX = -_sensitivity * (float)( pos.y - (_height / 2)) / _height;
		float rotY = -_sensitivity * (float)(pos.x - (_width / 2)) / _width;

		Vec3 newOrientation = _orientation;
		_orientation = Matrix3x3::RotationMatrix(rotY, _up) * _orientation;

		newOrientation = Matrix3x3::RotationMatrix(rotX, Vec3::Cross(_orientation, _up)) * _orientation;
		
		if (std::abs(Vec3::Dot(newOrientation, _up)) < 0.95f) {
			_orientation = newOrientation;
		}

		_mouse->SetCursorPos((_width / 2), (_height / 2));

		CalculateViewMatrix();
	}
}

void Camera::LockCursor(const bool lockState) {
	_cursorLocked = lockState;
	if (_cursorLocked) {
		//glfwSetInputMode(Renderer::instance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		_mouse->SetCursorHidden(_cursorLocked);
		
	}
	else {
		//glfwSetInputMode(Renderer::instance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		_mouse->SetCursorHidden(_cursorLocked);
		_firstClick = true;
		
	}
}
bool Camera::GetCursorLockState() {
	return _cursorLocked;
}