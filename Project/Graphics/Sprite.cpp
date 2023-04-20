
#include "Sprite.h"
#include "Renderer.h"
#include "../Util/Utility.h"
const unsigned int Sprite::_id = Utility::_idCount;

Sprite::Sprite() : Graphic() {
}

Sprite::Sprite(const char* path) : Graphic(path) {}
Sprite::~Sprite() {
	std::cout << "Deleting sprite\n";
}
void Sprite::Bind(const Matrix4x4* model) const {
	_shader->Activate();
	glUniformMatrix4fv(glGetUniformLocation( _shader->ID, "model"), 1, GL_TRUE, &model->buff[0]);
	Renderer::instance()->SetShaderVariables(_shader->ID);			
	const Texture* t = Renderer::instance()->GetTexture(_textureId);
	t->Bind();														
	t->texUni(_shader, "tex0", 0);									
	Renderer::instance()->GetVAO()->Bind();						
}
const unsigned int Sprite::ID()const { return _id; }