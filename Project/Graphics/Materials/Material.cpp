#include "Material.h"
#include "../Renderer.h"
Material::Material() : _shader(Renderer::instance()->GetShader(0)),
_texture(Renderer::instance()->LoadTexture("Assets/Textures/default.png")) {
	
}
Material::Material(const Shader* s, const char* texturePath) : 
	_shader(s), _texture(Renderer::instance()->LoadTexture(texturePath)) {

}
Material::~Material() {
	printf("deleting material base\n");
}
