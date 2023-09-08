#include "Material.h"
#include "../Renderer.h"
Material::Material() : _shader(Renderer::instance()->GetShader(0)),
_texture(Renderer::instance()->LoadTexture("Assets/Textures/default.png")) {
	_color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
}
Material::Material(const Shader* s, const char* texturePath) : 
	_shader(s), _texture(Renderer::instance()->LoadTexture(texturePath)) {
	_color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

}
Material::~Material() {
	printf("deleting material base\n");
}
const Texture* Material::GetTexture() const {
	return _texture;
}
/// <summary>
/// some optimisation can be added here if you have shader variables that dont change they can be bound once only
/// </summary>
/// <param name="model"></param>
void Material::Bind(const Matrix4x4* model) const {
	_shader->Activate();

	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "model"), 1, GL_TRUE, &model->buff[0]);
	Renderer::instance()->SetShaderVariables(_shader->ID);

	_texture->Bind();
	_texture->texUni(_shader, "tex0", 0);
	glUniform4f(glGetUniformLocation(_shader->ID, "color"), _color.x, _color.y, _color.z, _color.a);
}
void Material::Unbind()const {
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	
}