#ifndef MATERIAL_TEXT_H
#define MATERIAL_TEXT_H

#include "Material.h"
#include "../../BackEnd/VAO.h"

class MaterialUiText: public Material {

private:
	const VAO** _vao;
	

	
public :

	float _borderWidth;
	Vec2 _borderDirection;
	Vec3 _color;
	Vec3 _outlineColor;
	Vec3 _size;
	MaterialUiText();
	MaterialUiText(const char* texturePath, const VAO** vao);
	MaterialUiText(const Shader* shader ,const char* texturePath, const VAO** vao);
	~MaterialUiText();
	void Bind(const Matrix4x4* m) const override;
	void Unbind() const override;


};

#endif
