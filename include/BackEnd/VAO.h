#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"


class VAO
{
public :
	GLuint ID;
	VAO();
	void LinkAttrib(VBO* vbo, GLuint layout, GLuint numCompnents, GLenum type, GLsizeiptr stride, void* offset) const;
	void Bind() const ;
	void Unbind()const ;
	void Delete()const;
};
#endif

