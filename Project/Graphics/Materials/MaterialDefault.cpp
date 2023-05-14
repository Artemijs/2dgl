#include "MaterialDefault.h"
#include "../Renderer.h"
MaterialDefault::MaterialDefault(): Material() {
	//_shader = Renderer::instance()->GetShader(0);
}
MaterialDefault::MaterialDefault(const Shader* s, const char* texturePath): Material(s, texturePath) {

}
MaterialDefault::~MaterialDefault() {
	printf("deleting default material class\n");
}
void MaterialDefault::Bind(const Matrix4x4* model)const  {
	_shader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "model"), 1, GL_TRUE, &model->buff[0]);
	Renderer::instance()->SetShaderVariables(_shader->ID);
	_texture->Bind();
	_texture->texUni(_shader, "tex0", 0);
	Renderer::instance()->GetVAO()->Bind();
}

void MaterialDefault::Unbind()const {
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

}