#include "Graphics/Materials/DiffuseMaterial.h"
#include "Graphics/Renderer.h"
DiffuseMaterial::DiffuseMaterial() {


}
DiffuseMaterial::DiffuseMaterial(const Shader* s, const char* texturePath) {
	

}
DiffuseMaterial::~DiffuseMaterial() {


}

void DiffuseMaterial::Bind(const Matrix4x4* model) const {
	Renderer::instance()->SetShaderVariables(_shader->ID);

}
void DiffuseMaterial::Unbind()const {


}