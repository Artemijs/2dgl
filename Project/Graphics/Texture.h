#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "ShaderClass.h"
#include "../Math/Matrix4x4.h"

class Texture {
private:

public :
	GLuint ID;
	const char* _type;
	Vec2Int _size;
	Texture(const char* image, const char* type, GLenum slot);
	void texUni(const Shader* shader, const char* name, const GLuint unit)const;
	void Bind()const;
	void Unbind()const;
	void Delete();
};
#endif // !TEXTURE_H

