#ifndef MATERIAL_H
#define MATERIAL_H
#include "../../Math/Matrix4x4.h"
#include "../ShaderClass.h"
#include "../Texture.h"
class Material {

protected:
	bool _transparent;
	const Shader* _shader;
	const Texture* _texture;
	
public :
	Vec4 _color;
	Material();
	Material(const Shader* s, const char* texturePath);
	virtual ~Material();
	virtual void Bind(const Matrix4x4* model) const ;
	virtual void Unbind() const;
	const Texture* GetTexture()const;
	


};

#endif
