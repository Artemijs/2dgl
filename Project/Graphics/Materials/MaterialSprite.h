#ifndef MATERIAL_SPRITE_H
#define MATERIAL_SPRITE_H

#include "Material.h"


class MaterialSprite: public Material {

private:
	
public :
	MaterialSprite();
	MaterialSprite(const Shader* s, const char* texturePath);
	~MaterialSprite();
	void Bind(const Matrix4x4* m) const override;
	void Unbind() const override;


};

#endif
