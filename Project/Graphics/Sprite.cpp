
#include "Sprite.h"
#include "Renderer.h"
#include "../Util/Utility.h"
#include "Renderer.h"
const unsigned int Sprite::_component_id = Utility::GetID();
//9months of no fap
Sprite::Sprite() : Graphic(new MaterialUiSprite()){

}
Sprite::Sprite(BaseMaterial* m ) : Graphic(m) {

}

Sprite::Sprite(const char* path) : Graphic(new MaterialUiSprite(Renderer::instance()->GetShader(1), path)){

}
Sprite::~Sprite() {
	std::cout << "Deleting sprite\n";
	//delete _material;
}
const unsigned int Sprite::ID()const { return _component_id; }