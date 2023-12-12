#ifndef MATERIAL_H
#define MATERIAL_H
#include "Math/Matrix4x4.h"
#include "Graphics/ShaderClass.h"
#include "Graphics/Texture.h"
#include "Util/MemoryManager.h"
/*
	to do:
	Add camera bind to MAterial and remove Material Sprite


*/





/// <summary>
/// Has color and shader, binds color and model matrix
/// </summary>
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

/// <summary>
/// has BaseMaterial and texture array, models use multiple textures, 2d sprites just use 1
/// Binds textures and Projection matrix 
/// </summary>
class Material : public BaseMaterial{

protected:

	//const Texture* _texture;
	std::vector<const Texture*>* _textures;
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
	/// <summary>
	/// binds Textures andd perspective projection matrix, Base binds color and model
	/// </summary>
	/// <param name="model"></param>
	void Bind(const Matrix4x4* model) const override;

	void Unbind() const override;
	std::vector<const Texture*>* GetTexture() const;
	
	void AddTexture(const char* name, const char* filePath);


};

/// <summary>
/// has 1 texture and binds texture, ortho projection, no camera bind
/// </summary>
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

/// <summary>
/// PROBABLY DOESNT WORK
/// </summary>
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
