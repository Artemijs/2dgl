#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "../Math/Matrix4x4.h"
#include "../Game/BaseObject.h"
#include "Texture.h"
#include "ShaderClass.h"
#include <vector>
namespace v1_5{

	class Graphic : public BaseObject{
	protected:
		int _texId;
		Shader* _shader;

	public:
		Graphic();
		~Graphic();
		Graphic(const char* path, Vec3 pos, Vec3 size, float ang, BaseObject* parent = NULL);
		Shader* GetShader() { return _shader; }
		void SetShader(Shader* s) { _shader = s; }

	private: 
		virtual void BeforeDraw() = 0;

	protected:
		void AfterDraw();
	public:
		virtual void Draw() = 0;
		void TryDraw();
		Texture* GetTexture();
		void Update(float deltaTime);

	};
}
#endif
class Graphic {
private:
	const unsigned int _textureId;
	const Shader* _shader;
public:
	Graphic();
	~Graphic();
	Graphic(const char* path);
	void Bind();
	void Draw();
	void Unbind();
};
/*

	int texId
	int shaderId
	transform
	Matrix4x4 _model


	Bind
	Draw
	Unbind



class Graphic : public BaseObject{
protected:
	const unsigned int _texId;
	Shader* _shader;

public:
	Graphic();
	~Graphic();
	Graphic(const char* path, Vec3 pos, Vec3 size, float ang, BaseObject* parent = NULL);
	Shader* GetShader() { return _shader; }
	void SetShader(Shader* s) { _shader = s; }

private: 
	virtual void BeforeDraw() = 0;

protected:
	void AfterDraw();
public:
	virtual void Draw() = 0;
	void TryDraw();
	Texture* GetTexture();
	void Update(float deltaTime);

};


*/