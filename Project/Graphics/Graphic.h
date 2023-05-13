#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "../Math/Matrix4x4.h"
#include "Texture.h"
#include "ShaderClass.h"
#include <vector>
#include "../Game/BaseComponent.h"
#include "../Graphics/Material.h"
class Graphic : public BaseComponent{
protected:
	const Material* _baseMaterial;
public:
	Graphic();
	Graphic(const Material* m);
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