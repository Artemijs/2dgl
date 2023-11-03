#ifndef MATERIAL_H
#define MATERIAL_H
#include "../../Math/Matrix4x4.h"
#include "../ShaderClass.h"
#include "../Texture.h"
#include "../../Util/MemoryManager.h"

class BaseMaterial : public Memory{
protected:
	bool _transparent;
	const Shader* _shader;


public :
	Vec4 _color;
	BaseMaterial();
	BaseMaterial(const Shader* s);
	~BaseMaterial();
	virtual void Bind(const Matrix4x4* model) const;
	/// <summary>
	/// unbinds the VAO , TEXTURE and SHADER
	/// </summary>
	virtual void Unbind() const;
	const Shader* GetShader()const ;
};


class Material : public BaseMaterial{

protected:

	const Texture* _texture;
public :
	/// <summary>
	/// Default construcrtor sets the texture to "Assets/Textures/default.png" and the shader to GetShader(1)
	/// </summary>
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

class MaterialUI : public BaseMaterial {

protected:

	const Texture* _texture;
public:
	MaterialUI();
	MaterialUI(const Shader* s, const char* texturePath);
	/// <summary>
	/// shaders and textures get deleted in renderer
	/// </summary>
	virtual ~MaterialUI();
	void Bind(const Matrix4x4* model) const override;
	void Unbind() const override;
	const Texture* GetTexture()const;

};


class MaterialUiNoTex : public BaseMaterial {
protected:

public:
	MaterialUiNoTex();
	MaterialUiNoTex(const Shader* s);
	/// <summary>
	/// shaders and textures get deleted in renderer
	/// </summary>
	virtual ~MaterialUiNoTex();
	void Bind(const Matrix4x4* model) const override;
	void Unbind() const override;
};
#endif
