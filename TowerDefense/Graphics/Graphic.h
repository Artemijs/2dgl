#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "../Math/Matrix4x4.h"
#include "../Game/BaseObject.h"
#include "Texture.h"
#include "ShaderClass.h"
#include <vector>

class Graphic : public BaseObject{
protected:
	int _texId;
	Shader* _shader;

public:
	Graphic();
	~Graphic();
	Graphic(const char* path, Vec3 pos, Vec3 size, float ang);
	Shader* GetShader() { return _shader; }
	void SetShader(Shader* s) { _shader = s; }

private: 
	virtual void BeforeDraw() = 0;

protected:
	void AfterDraw();
public:
	virtual void Draw() = 0;
	void TryDraw();
	Texture* GetTexture();
	void Update(float deltaTime);
	

	

};

#endif