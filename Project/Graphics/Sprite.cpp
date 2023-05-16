
#include "Sprite.h"
#include "Renderer.h"
#include "../Util/Utility.h"
#include "Renderer.h"
const unsigned int Sprite::_component_id = Utility::GetID();
//9months of no fap
Sprite::Sprite() : Graphic(new MaterialDefault()){
}
Sprite::Sprite(Material* m ) : Graphic(m) {
}

Sprite::Sprite(const char* path) : Graphic(new MaterialDefault(Renderer::instance()->GetShader(0), path)){
}
Sprite::~Sprite() {
	std::cout << "Deleting sprite\n";
	//delete _material;
}
const unsigned int Sprite::ID()const { return _component_id; }