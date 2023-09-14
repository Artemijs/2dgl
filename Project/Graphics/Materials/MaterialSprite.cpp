#include "MaterialSprite.h"
#include "../Renderer.h"
MaterialSprite::MaterialSprite(): Material() {
}
MaterialSprite::MaterialSprite(const Shader* s, const char* texturePath): Material(s, texturePath) {
}				
MaterialSprite::~MaterialSprite() {
	printf("deleting default material class\n");
}						
void MaterialSprite::Bind(const Matrix4x4* model)const  {
	Material::Bind(model);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "view"), 1, GL_TRUE, Renderer::instance()->GetCamera()->GetCamera()->buff);
	Renderer::instance()->GetVAO()->Bind();
}						
						
void MaterialSprite::Unbind()const {
	Material::Unbind();

}