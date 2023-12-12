#include "Graphics/Materials/MaterialUISprite.h"
#include "Graphics/Renderer.h"
MaterialUiSprite::MaterialUiSprite(): MaterialUI() {
}

MaterialUiSprite::MaterialUiSprite(const char* texturePath) : MaterialUI(Renderer::instance()->GetShader(1), texturePath) {

}

MaterialUiSprite::MaterialUiSprite(const Shader* s, const char* texturePath): MaterialUI(s, texturePath) {

}

MaterialUiSprite::~MaterialUiSprite() {
	printf("dewleting MAterial Ui sprite\n");
}						
void MaterialUiSprite::Bind(const Matrix4x4* model)const  {
	MaterialUI::Bind(model);
	Renderer::instance()->GetVAO()->Bind();
}						
						
void MaterialUiSprite::Unbind()const {
	MaterialUI::Unbind();

}