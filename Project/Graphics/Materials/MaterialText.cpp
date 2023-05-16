#include "MAterialText.h"
#include "../Renderer.h"
MaterialText::MaterialText():
	Material(Renderer::instance()->GetShader(1), "Assets/Textures/btn.png")
{
}
MaterialText::MaterialText(const char* texturePath, const VAO** vao):
	Material(Renderer::instance()->GetShader(1), texturePath),
	_vao(vao)
{

}MaterialText::MaterialText(const Shader* shader, const char* texturePath, const VAO** vao) :
	Material(Renderer::instance()->GetShader(1), texturePath),
	_vao(vao)
{

}
MaterialText::~MaterialText() {
	printf("deleting default material class\n");
}
void MaterialText::Bind(const Matrix4x4* model)const  {
	/*_shader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "model"), 1, GL_TRUE, &_model.buff[0]);
	Renderer::instance()->SetShaderVariables(_shader);
	Renderer::instance()->GetTexture(_texId)->Bind();
	Renderer::instance()->GetTexture(_texId)->texUni(_shader, "tex0", 0);

	glUniform1f(glGetUniformLocation(_shader->ID, "borderWidth"), _borderWidth);
	glUniform2f(glGetUniformLocation(_shader->ID, "offset"), _borderDirection.x, _borderDirection.y);
	glUniform3f(glGetUniformLocation(_shader->ID, "color"), _color.x, _color.y, _color.z);
	glUniform3f(glGetUniformLocation(_shader->ID, "outlineColor"), _borderColor.x, _borderColor.y, _borderColor.z);
	_vao->Bind();
	*/
	_shader->Activate();

	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "model"), 1, GL_TRUE, &model->buff[0]);
	Renderer::instance()->SetShaderVariables(_shader->ID);
	
	_texture->Bind();
	_texture->texUni(_shader, "tex0", 0);

	glUniform1f(glGetUniformLocation(_shader->ID, "borderWidth"), _borderWidth);
	glUniform2f(glGetUniformLocation(_shader->ID, "offset"), _borderDirection.x, _borderDirection.y);
	glUniform3f(glGetUniformLocation(_shader->ID, "color"), _color.x, _color.y, _color.z);
	glUniform3f(glGetUniformLocation(_shader->ID, "outlineColor"), _outlineColor.x, _outlineColor.y, _outlineColor.z);

	(*_vao)->Bind();
}

void MaterialText::Unbind()const {
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

}