#include "MaterialUISprite.h"
#include "../Renderer.h"
MaterialUiSprite::MaterialUiSprite(): Material() {
}
MaterialUiSprite::MaterialUiSprite(const Shader* s, const char* texturePath): Material(s, texturePath) {
}				
MaterialUiSprite::~MaterialUiSprite() {
	printf("deleting default material class\n");
}						
void MaterialUiSprite::Bind(const Matrix4x4* model)const  {
	Material::Bind(model);
	Renderer::instance()->GetVAO()->Bind();
}						
						
void MaterialUiSprite::Unbind()const {
	Material::Unbind();

}