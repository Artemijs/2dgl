#ifndef MATERIAL_UI_SPRITE_H
#define MATERIAL_UI_SPRITE_H

#include "Material.h"


class MaterialUiSprite: public MaterialUI {

private:
	
public :
	/// <summary>
	/// ui materials are not affected by camera so they have to be z = -1
	/// </summary>
	MaterialUiSprite();
	/// <summary>
	/// ui materials are not affected by camera so they have to be z = -1
	/// </summary>
	MaterialUiSprite(const Shader* s, const char* texturePath);
	/// <summary>
	/// ui materials are not affected by camera so they have to be z = -1
	/// </summary>
	/// <param name="texturePath">uses shader(1)</param>
	MaterialUiSprite(const char* texturePath);
	~MaterialUiSprite();
	void Bind(const Matrix4x4* m) const override;
	void Unbind() const override;


};

#endif
