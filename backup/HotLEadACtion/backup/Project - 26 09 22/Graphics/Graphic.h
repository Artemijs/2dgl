#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "../Math/Matrix4x4.h"
#include "Texture.h"
#include "ShaderClass.h"
struct SpriteData
{
public:
	Vec3 _position;
	Vec2 _size;
	float _angle;
};


class Graphic {
protected:
	SpriteData _rect;
	Matrix4x4 _model;
	int _texId;
	Shader* _shader;
public:
	Graphic();
	~Graphic();
	Graphic(const char* path, SpriteData spData);

	Shader* GetShader() { return _shader; }
	void SetShader(Shader* s) { _shader = s; }

private: virtual void BeforeDraw() = 0;
public:  virtual void Draw() = 0;
protected: void AfterDraw();
public:
	Matrix4x4 MakeModelMatrix();

	Matrix4x4 GetMatrix();
	Texture* GetTexture();
	SpriteData GetSpriteData();
	
	void SetSize(Vec2 size);
	void SetPosition(Vec3 pos);
	void SetAngle(float angle);
	static SpriteData MakeSPD(Vec3 pos, Vec2 size, float ang);

};

#endif