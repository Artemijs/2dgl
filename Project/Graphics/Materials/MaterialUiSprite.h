#ifndef MATERIAL_UI_SPRITE_H
#define MATERIAL_UI_SPRITE_H

#include "Material.h"


class MaterialUiSprite: public MaterialUI {

private:
	
public :
	MaterialUiSprite();
	MaterialUiSprite(const Shader* s, const char* texturePath);
	MaterialUiSprite(const char* texturePath);
	~MaterialUiSprite();
	void Bind(const Matrix4x4* m) const override;
	void Unbind() const override;


};

#endif
