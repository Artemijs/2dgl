#ifndef MATERIAL_H
#define MATERIAL_H
#include "../../Math/Matrix4x4.h"
#include "../ShaderClass.h"
#include "../Texture.h"
class Material {

protected:
	const Shader* _shader;
	const Texture* _texture;
public :
	Material();
	Material(const Shader* s, const char* texturePath);
	virtual ~Material();
	virtual void Bind(const Matrix4x4* model) const = 0;
	virtual void Unbind() const = 0;


};

#endif
