#ifndef MATERIAL_H
#define MATERIAL_H
#include "../Math/Matrix4x4.h"
#include "ShaderClass.h"
class Material {

private:
	const Shader* _shader;
public :
	Material();
	Material(const Shader* s);
	~Material();
	virtual void Bind(const Matrix4x4& m) const = 0;
	virtual void Unbind() const = 0;


};

#endif
