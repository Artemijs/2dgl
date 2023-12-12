#include "Graphics/Materials/MaterialSprite.h"
#include "Graphics/Renderer.h"
MaterialSprite::MaterialSprite(): Material() {
	_shader = Renderer::instance()->GetShader(7);
}
MaterialSprite::MaterialSprite(const Shader* s, const char* texturePath): Material(s, texturePath) {

}				
MaterialSprite::~MaterialSprite() {
	printf("deleting default material class\n");
}						
void MaterialSprite::Bind(const Matrix4x4* model) const {
	Material::Bind(model);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "view"), 1, GL_TRUE,
		&Renderer::instance()->GetCamera()->GetViewMatrix()->buff[0]);
	Renderer::instance()->GetVAO()->Bind();
}						
						
void MaterialSprite::Unbind()const {
	Material::Unbind();

}