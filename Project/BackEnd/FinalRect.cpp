#include "FinalRect.h"
#include <glad/glad.h>
//VAO _vao;
FinalRect::FinalRect() {
	
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	glBindVertexArray(0);
	glBindBuffer( GL_ARRAY_BUFFER, 0);
	_shader = new Shader("Assets/Shaders/final_rect.vert", "Assets/Shaders/final_rect.frag");
}
void FinalRect::Bind() {
	glBindVertexArray(_vao);
	_shader->Activate();
}
void FinalRect::Unbind() {
	glBindVertexArray(0);
	glUseProgram(0);
}
FinalRect::~FinalRect() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
}