#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "../Math/Matrix4x4.h"
#include "Texture.h"
#include "ShaderClass.h"
#include <vector>
#include "../Game/BaseComponent.h"

class Graphic : public BaseComponent{
protected:
	const unsigned int _textureId;
	const Shader* _shader;
private:
	virtual void Bind(const Matrix4x4* model) const = 0;
	void Unbind() const;
public:
	Graphic();
	Graphic(const char* path);
	~Graphic();

	void Draw(const Matrix4x4* model) const;

};



#endif

/*

	int texId
	int shaderId

	Bind
	Draw
	Unbind



class Graphic : public BaseObject{
protected:
	const unsigned int _texId;
	Shader* _shader;

public:
	Graphic();
	~Graphic();
	Graphic(const char* path, Vec3 pos, Vec3 size, float ang, BaseObject* parent = NULL);
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


*/