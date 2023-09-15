#include "Camera.h"

Camera::Camera() {
	_up = Vec3(0.0f, 1.0f, 0.0f);
	_orientation = Vec3(0.0f, 0.0f, -1.0f);
}

Camera::Camera(unsigned int height, unsigned int width, Vec3 position) : _width(width), _height(height), _position(position){
	_up = Vec3(0.0f, 1.0f, 0.0f);
	_orientation = Vec3(0.0f, 0.0f, 1.0f);

}
void Camera::CalculateViewMatrix() {
	
	Vec3 Z = _orientation;
	Vec3 X = Vec3::Cross(_up, Z);
	X.Normalize();
	Vec3 Y = Vec3::Cross(Z, X);
	Y.Normalize();
	_viewMatrix = Matrix4x4::GetCameraMatrix(X, Y, Z, _position);
}
Matrix4x4* Camera::GetCamera() {
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