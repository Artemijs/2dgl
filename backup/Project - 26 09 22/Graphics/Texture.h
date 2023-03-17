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
	GLenum type;
	Vec2Int _size;
	Texture(const char* image, GLenum textType, GLenum slot, GLenum format, GLenum pixelType);
	void texUni(Shader* shader, const char* name, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};
#endif // !TEXTURE_H

