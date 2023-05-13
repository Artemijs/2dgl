#ifndef MATERIAL_DEFAULT_H
#define MATERIAL_DEFAULT_H

#include "Material.h"


class MaterialDefault: public Material {

private:
	
public :
	MaterialDefault();
	MaterialDefault(const Shader* s, const char* texturePath);
	~MaterialDefault();
	void Bind(const Matrix4x4* m) const override;
	void Unbind() const override;


};

#endif
