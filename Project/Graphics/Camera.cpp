#include "Camera.h"
#include "Renderer.h"
Camera::Camera() {
	_up = Vec3(0.0f, 1.0f, 0.0f);
	_orientation = Vec3(0.0f, 0.0f, -1.0f);
	_ang = Vec2();
	_sensitivity = 1.1f;
	_firstClick = true;
	_x = false;
	_cursorLocked = false;
	_angles = Vec3();
}

Camera::Camera(unsigned int height, unsigned int width, Vec3 position) : _width(width), _height(height), _position(position){
	_up = Vec3(0.0f, 1.0f, 0.0f);
	_orientation = Vec3(1.0f, 0.0f, 0.0f);
	_ang = Vec2();					
	_sensitivity = 1.1f;			
	_firstClick = true;					
	_cursorLocked = false;			
	_x = false;			
	_angles = Vec3(0, 1, 0);
}
#include "../Util/Utility.h"
void Camera::CalculateViewMatrix() {
	
	/*Vec3 Z = _orientation;
	Vec3 X = Vec3::Cross(_up, Z);
	X.Normalize();
	Vec3 Y = Vec3::Cross(Z, X);
	Y.Normalize();
	_viewMatrix = Matrix4x4::GetCameraMatrix(X, Y, Z, Vec3());*/
	//float a = Utility::Deg2Rad(15);
	//_angles = Vec3(a, a, a);
	Matrix4x4 zRot = Matrix4x4::RotationMatrix(_angles.z);
	
	Matrix4x4 xRot(1.0f);
	xRot.buff[5] = cosf(_angles.x);
	xRot.buff[6] = -sinf(_angles.x);
	xRot.buff[9] = sinf(_angles.x);
	xRot.buff[10] = cosf(_angles.x);
	
	Matrix4x4 yRot(1.0f);
	yRot.buff[0] = cosf(_angles.y);
	yRot.buff[2] = sinf(_angles.y);
	yRot.buff[8] = -sinf(_angles.y);
	yRot.buff[10] = cosf(_angles.y);

	_viewMatrix = xRot * yRot * Matrix4x4::TranslationMatrix(_position);
	//_viewMatrix = Matrix4x4::RotationMatrix(_angles.y, Vec3(0, 1, 0)) * _viewMatrix;
	//_viewMatrix = Matrix4x4::TranslationMatrix(_position) * _viewMatrix;


}
Matrix4x4* Camera::GetCamera() {
	return &_viewMatrix;
}
Vec3 Camera::GetPosition() {
	return _position;
}
#include "../Util/Utility.h"
void Camera::SetPosition(Vec3 pos) {
	//Utility::PrintVector(" camera offset", pos);
	_position = pos;
}

Vec3 Camera::GetOrientation() {
	return _orientation;
}

void Camera::SetOrientation(Vec3 dir) {
	_orientation = dir;
}

#include "../Util/Utility.h"
void Camera::MouseMove(const double& xpos, const double& ypos) {

	if (_cursorLocked) {
		if (_firstClick) {
			glfwSetCursorPos(Renderer::instance()->GetWindow(), (_width / 2), (_height / 2));
			_firstClick = false;
			return;
		}

		float rotX = -_sensitivity * (float)(ypos - (_height / 2)) / _height;
		float rotY = _sensitivity * (float)(xpos - (_width / 2)) / _width;
		//printf(" angle %.3f \n", rotY);
		/*if (!_x) {
			_orientation += Matrix3x3::RotationMatrix(rotX, Vec3::Cross(_orientation, _up)) * _orientation;
			//_up = Vec3::Cross(_up, Vec3(1, 0, 0));
			//_orientation = Matrix3x3::RotationMatrix(rotX, Vec3(1.0f, 0, 0)) * _orientation;
			_orientation.Normalize();
		}
		else {
			_orientation = Matrix3x3::RotationMatrix(rotY, _up) * _orientation;
		}*/
		// Decides whether or not the next vertical Orientation is legal or not				 
		/*if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}*/
		_angles += Vec3(rotX, rotY, 0);
		//_orientation = Matrix3x3::RotationMatrix(rotY, _up) * _orientation;
		Vec3 vAxis = Vec3(0.0f, 0.0f, 1.0f);//Vec3::Cross(_orientation, _up);
		float testRotation = Utility::Deg2Rad(1);
		_orientation = Matrix3x3::RotationMatrix(testRotation, vAxis) * _orientation;
		
		
		//Utility::PrintVector("forward :", _orientation);


		glfwSetCursorPos(Renderer::instance()->GetWindow(), (_width / 2), (_height / 2));

		CalculateViewMatrix();
	}
}

void Camera::LockCursor(const bool lockState) {
	_cursorLocked = lockState;
	if (_cursorLocked) {
		glfwSetInputMode(Renderer::instance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
	}
	else {
		glfwSetInputMode(Renderer::instance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		_firstClick = true;
		
	}
}
bool Camera::GetCursorLockState() {
	return _cursorLocked;
}