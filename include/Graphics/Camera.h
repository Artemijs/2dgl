#ifndef CAMERA_H
#define CAMERA_H
#include "Math/Matrix4x4.h"
#include "Input/Mouse.h"
/// <summary>
/// To rotate this i could add pitch roll and yaw , create 3 matrices out off them
/// multiply them together to get the final rotation matrix and use that to create the came view matrix
/// 
/// </summary>
class Camera {
private:
	Matrix4x4 _viewMatrix;
	Vec3 _position;
	Vec3 _orientation;
	Vec3 _up;

	unsigned int _width;
	unsigned int _height;

	float _speed;
	float _sensitivity;
	bool _cursorLocked;
	bool _firstClick;
	Mouse* _mouse;

public:
	bool _x;
	Camera();
	Camera(unsigned int height, unsigned int width, Vec3 position);
	/// <summary>
	/// comptue the forward right adn up vectors and create the view matrix
	/// </summary>
	void CalculateViewMatrix();

	Matrix4x4* GetViewMatrix();
	Vec3 GetPosition();
	void SetPosition(Vec3 pos);
	Vec3 GetOrientation();
	void SetOrientation(Vec3 dir);
	void MouseMove();
	void LockCursor(const bool lockState);
	bool GetCursorLockState();
};
#endif // !CAMERA_H
