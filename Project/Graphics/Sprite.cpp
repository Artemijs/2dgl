
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
void Sprite::Bind(Matrix4x4* model) const {
	const unsigned int id = _shader->ID;
	glUseProgram(id);
	glUniformMatrix4fv(glGetUniformLocation(id, "model"), 1, GL_TRUE, &model->buff[0]);
	Renderer::instance()->SetShaderVariables(id);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	//Renderer::instance()->GetTexture(_texId)->texUni(_shader, "tex0", 0);
	Renderer::instance()->GetVAO()->Bind();
}
const unsigned int Sprite::ID() { return _id; }