#ifndef MATERIAL_BUTTON_H
#define MATERIAL_BUTTON_H

#include "Graphics/Materials/Material.h"


class MaterialUiButton: public MaterialUI {

private:
	const Vec2 _texScale;
	
public :
	Vec2 _uvOffset;
	MaterialUiButton();
	MaterialUiButton(const char* texturePath);
	~MaterialUiButton();
	void Bind(const Matrix4x4* m) const override;
	void Unbind() const override;


};

#endif
