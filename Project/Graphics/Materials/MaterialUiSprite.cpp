#include "MaterialUISprite.h"
#include "../Renderer.h"
MaterialUiSprite::MaterialUiSprite(): MaterialUI() {
}

MaterialUiSprite::MaterialUiSprite(const char* texturePath) : MaterialUI(Renderer::instance()->GetShader(1), texturePath) {

}

MaterialUiSprite::MaterialUiSprite(const Shader* s, const char* texturePath): MaterialUI(s, texturePath) {

}

MaterialUiSprite::~MaterialUiSprite() {
	printf("deleting default material class\n");
}						
void MaterialUiSprite::Bind(const Matrix4x4* model)const  {
	MaterialUI::Bind(model);
	Renderer::instance()->GetVAO()->Bind();
}						
						
void MaterialUiSprite::Unbind()const {
	MaterialUI::Unbind();

}