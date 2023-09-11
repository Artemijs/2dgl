#ifndef MATERIAL_H
#define MATERIAL_H
#include "../../Math/Matrix4x4.h"
#include "../ShaderClass.h"
#include "../Texture.h"


class BaseMaterial {
protected:
	bool _transparent;
	const Shader* _shader;


public :
	Vec4 _color;
	BaseMaterial();
	BaseMaterial(const Shader* s);
	~BaseMaterial();
	virtual void Bind(const Matrix4x4* model) const;
	virtual void Unbind() const;
};


class Material : public BaseMaterial{

protected:

	const Texture* _texture;
public :
	Material();
	Material(const Shader* s, const char* texturePath);
	/// <summary>
	/// shaders and textures get deleted in renderer
	/// </summary>
	virtual ~Material();
	void Bind(const Matrix4x4* model) const override;
	void Unbind() const override;
	const Texture* GetTexture()const;
	


};

#endif
