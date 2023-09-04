#include "MAterialText.h"
#include "../Renderer.h"

/// <summary>
/// changed BINd function not tested
/// </summary>
MaterialText::MaterialText():
	Material(Renderer::instance()->GetShader(2), "Assets/Textures/btn.png")
{
}
MaterialText::MaterialText(const char* texturePath, const VAO** vao):
	Material(Renderer::instance()->GetShader(2), texturePath),
	_vao(vao)
{

}MaterialText::MaterialText(const Shader* shader, const char* texturePath, const VAO** vao) :
	Material(Renderer::instance()->GetShader(2), texturePath),
	_vao(vao)
{

}
MaterialText::~MaterialText() {
	printf("deleting default material class\n");
}
#include "../Renderer.h"
void MaterialText::Bind(const Matrix4x4* model)const  {
	_shader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "model"), 1, GL_TRUE, &model->buff[0]);
	Renderer::instance()->SetShaderVariables(_shader->ID);
	
	_texture->Bind();
	_texture->texUni(_shader, "tex0", 0);

	//Material::Bind(model);

	glUniform1f(glGetUniformLocation(_shader->ID, "borderWidth"), _borderWidth);
	glUniform2f(glGetUniformLocation(_shader->ID, "offset"), _borderDirection.x, _borderDirection.y);
	glUniform3f(glGetUniformLocation(_shader->ID, "color"), _color.x, _color.y, _color.z);
	glUniform3f(glGetUniformLocation(_shader->ID, "outlineColor"), _outlineColor.x, _outlineColor.y, _outlineColor.z);
	(*_vao)->Bind();
}

void MaterialText::Unbind()const {
	(*_vao)->Unbind();
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glUseProgram(0);
	Material::Unbind();

}