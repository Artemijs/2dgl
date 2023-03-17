#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "../Math/Matrix4x4.h"
#include "Texture.h"
#include "ShaderClass.h"

class Graphic {
protected:
	float _angle;
	Matrix4x4 _transform;
	Matrix4x4 _rotation;
	Matrix4x4 _scale;
	int _texId;
	Shader* _shader;
public:
	Graphic();
	~Graphic();
	Graphic(const char* path, Vec3 pos, Vec3 size, float ang);

	Shader* GetShader() { return _shader; }
	void SetShader(Shader* s) { _shader = s; }

private: virtual void BeforeDraw() = 0;
public:  virtual void Draw() = 0;
protected: void AfterDraw();
public:
	//Matrix4x4 MakeModelMatrix();
	//Matrix4x4 MakeModelMatrix(Matrix4x4 offset);

	//Matrix4x4 GetMatrix();
	Texture* GetTexture();
	float GetAngle();
	Vec3 GetPosition();
	Vec3 GetSize();
	void SetSize(Vec3 size);
	void SetPosition(Vec3 pos);
	void SetAngle(float angle);
	

};

#endif