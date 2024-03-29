#include "Graphics/Materials/MaterialUiButton.h"
#include "Graphics/Renderer.h"
MaterialUiButton::MaterialUiButton():
	MaterialUI(Renderer::instance()->GetShader(2), ASSETS"Textures/btn.png"),
	_texScale(Vec2(1, 0.25f)),
	_uvOffset(Vec2(0, 3)){
	//_shader = Renderer::instance()->GetShader(0);
}
MaterialUiButton::MaterialUiButton(const char* texturePath): 
	MaterialUI(Renderer::instance()->GetShader(2), texturePath),
	_texScale(Vec2(1, 0.25f)),
	_uvOffset( Vec2(0, 3)){

}
MaterialUiButton::~MaterialUiButton() {
	printf("deleting default material class\n");
}
void MaterialUiButton::Bind(const Matrix4x4* model)const  {
	MaterialUI::Bind(model);

	glUniform2f(glGetUniformLocation(_shader->ID, "uvOff"), _uvOffset.x, _uvOffset.y);
	glUniform2f(glGetUniformLocation(_shader->ID, "uv_scale"), _texScale.x, _texScale.y);
	Renderer::instance()->GetVAO()->Bind();
}

void MaterialUiButton::Unbind()const {
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

}