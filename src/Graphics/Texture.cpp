#include "Graphics/Texture.h"
#include <stb_image.h>

Texture::Texture(const char* image, const char* type, GLenum slot) {
	//							LOADD TEXTURE FILE
	_type = type;
	_size = Vec2Int();
	int numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &_size.x, &_size.y, &numColCh, 4);
	
	//							CREATE OPENGL TEXTURE
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (numColCh == 4) {
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			_size.x,
			_size.y,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes
		);
	}
	else if (numColCh == 3) {
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			_size.x,
			_size.y,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bytes
		);
	}
	else if (numColCh == 1) {
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			_size.x,
			_size.y,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bytes
		);
	}
	else
		throw std::invalid_argument("Automatic Texture type recognition failed");

	glGenerateMipmap(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, 0);

	
	stbi_image_free(bytes);
}
void Texture::texUni(const Shader* shader, const GLuint unit) const {
	shader->Activate();
	GLuint tex0Uni = glGetUniformLocation(shader->ID, _type);
	glUniform1i(tex0Uni, unit);
}
void Texture::Bind()const {
	glBindTexture(GL_TEXTURE_2D, ID);
}
void Texture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}