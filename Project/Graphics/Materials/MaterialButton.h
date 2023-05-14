#ifndef MATERIAL_BUTTON_H
#define MATERIAL_BUTTON_H

#include "Material.h"


class MaterialButton: public Material {

private:
	const Vec2 _texScale;
	
public :
	Vec2 _uvOffset;
	MaterialButton();
	MaterialButton(const char* texturePath);
	~MaterialButton();
	void Bind(const Matrix4x4* m) const override;
	void Unbind() const override;


};

#endif
