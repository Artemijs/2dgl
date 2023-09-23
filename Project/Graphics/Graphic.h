#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "../Math/Matrix4x4.h"
#include "Texture.h"
#include "ShaderClass.h"
#include <vector>
#include "../Game/BaseComponent.h"
#include "../Graphics/Materials/Material.h"


/// <summary>
/// to do change all the material to base materail
/// </summary>
class Graphic : public BaseComponent{
protected:
	Material* _baseMaterial;
	//for the glDraw call that text also uses and has more than 6 indices
	unsigned int _indexCount;

public:
	Graphic(const unsigned int indexCount = 6);
	Graphic(Material* m, const unsigned int indexCount = 6);
	~Graphic();

	virtual void Draw(const Matrix4x4* model) const;
	Material* GetMaterial() const ;
	void SetMaterial(Material* m);
	const unsigned int IndexCount();

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