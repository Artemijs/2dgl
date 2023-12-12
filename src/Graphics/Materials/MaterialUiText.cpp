#include "Graphics/Materials/MaterialUiText.h"
#include "Graphics/Renderer.h"

/// <summary>
/// changed BINd function not tested
/// </summary>
MaterialUiText::MaterialUiText():
	Material(Renderer::instance()->GetShader(3), "Assets/Textures/btn.png")
{
}
MaterialUiText::MaterialUiText(const char* texturePath, const VAO** vao):
	Material(Renderer::instance()->GetShader(3), texturePath),
	_vao(vao)
{

}MaterialUiText::MaterialUiText(const Shader* shader, const char* texturePath, const VAO** vao) :
	Material(Renderer::instance()->GetShader(3), texturePath),
	_vao(vao)
{

}
MaterialUiText::~MaterialUiText() {
	printf("deleting default material class\n");
}
#include "Graphics/Renderer.h"
void MaterialUiText::Bind(const Matrix4x4* model)const  {
	Renderer* r = Renderer::instance();
	_shader->Activate();
	
	
	auto proj = r->GetUIProjection();
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "proj"), 1, GL_TRUE, proj->buff);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "model"), 1, GL_TRUE, model->buff);
	
	_textures->at(0)->Bind();
	_textures->at(0)->texUni(_shader, 0);

	//Material::Bind(model);

	glUniform1f(glGetUniformLocation(_shader->ID, "borderWidth"), _borderWidth);
	glUniform2f(glGetUniformLocation(_shader->ID, "offset"), _borderDirection.x, _borderDirection.y);
	glUniform3f(glGetUniformLocation(_shader->ID, "color"), _color.x, _color.y, _color.z);
	glUniform3f(glGetUniformLocation(_shader->ID, "outlineColor"), _outlineColor.x, _outlineColor.y, _outlineColor.z);
	(*_vao)->Bind();
	//r->GetVAO()->Bind();
}

void MaterialUiText::Unbind()const {
	(*_vao)->Unbind();
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glUseProgram(0);
	Material::Unbind();

}