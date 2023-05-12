#include "Material.h"
#include "Renderer.h"
Material::Material() {
	_shader = Renderer::instance()->GetShader(0);
}
Material::Material(const Shader* s): _shader(s) {
}
Material::~Material() {

}
