#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO* vbo, GLuint layout, GLuint numCompnents, GLenum type, GLsizeiptr stride, void* offset) const {
	vbo->Bind();
	glVertexAttribPointer(layout, numCompnents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo->Unbind();
}
void VAO::Bind() const {
	glBindVertexArray(ID);
}

void VAO::Unbind() const {
	glBindVertexArray(0);
}
void VAO::Delete() const {
	glDeleteVertexArrays(1, &ID);
}