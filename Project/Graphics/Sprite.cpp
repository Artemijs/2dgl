
#include "Sprite.h"
#include "Renderer.h"
#include "../Util/Utility.h"
#include "Renderer.h"
const unsigned int Sprite::_component_id = Utility::GetID();
//9months of no fap
Sprite::Sprite() : _material( new MaterialDefault()){
	_baseMaterial = _material;
}

Sprite::Sprite(const char* path) : 
	_material(new MaterialDefault(Renderer::instance()->GetShader(0), path)){
	_baseMaterial = _material;
}
Sprite::~Sprite() {
	std::cout << "Deleting sprite\n";
	delete _material;
}
const unsigned int Sprite::ID()const { return _component_id; }