#ifndef DIFFUSE_MATERIAL_H
#define DIFFUSE_MATERIAL_H
#include "Math/Matrix4x4.h"
#include "Graphics/ShaderClass.h"
#include "Graphics/Texture.h"
#include "Graphics/Materials/Material.h"



/// <summary>
/// probably doesnt even work
/// </summary>
class DiffuseMaterial: public Material{

protected:

public :
	DiffuseMaterial();
	DiffuseMaterial(const Shader* s, const char* texturePath);
	virtual ~DiffuseMaterial();
	void Bind(const Matrix4x4* model) const override;
	void Unbind() const override;
	//const Texture* GetTexture() const;
};

#endif
