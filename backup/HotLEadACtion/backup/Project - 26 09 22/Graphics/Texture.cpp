#include "Texture.h"

Texture::Texture(const char* image, GLenum textType, GLenum slot, GLenum format, GLenum pixelType) {
	//texture
	type = textType;
	_size = Vec2Int();
	int numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &_size.x, &_size.y, &numColCh, 4);
	

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(textType, ID);
	glTexParameteri(textType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(textType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(textType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(textType, 0, GL_RGBA, _size.x, _size.y, 0, format, pixelType, bytes);
	glGenerateMipmap(textType);


	glBindTexture(textType, 0);

	
	stbi_image_free(bytes);
}
void Texture::texUni(Shader* shader, const char* name, GLuint unit) {
	shader->Activate();
	GLuint tex0Uni = glGetUniformLocation(shader->ID, name);
	glUniform1i(tex0Uni, unit);
}
void Texture::Bind() {
	glBindTexture(type, ID);
}
void Texture::Unbind() {
	glBindTexture(type, 0);
}
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}