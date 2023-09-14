#ifndef CAMERA_H
#define CAMERA_H
#include "../Math/Matrix4x4.h"

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

public:
	Camera();
	Camera(unsigned int height, unsigned int width, Vec3 position);
	void CalculateViewMatrix();
	Matrix4x4* GetCamera();
	Vec3 GetPosition();
	void SetPosition(Vec3 pos);
};
#endif // !CAMERA_H
