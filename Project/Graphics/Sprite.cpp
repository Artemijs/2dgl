
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
	const unsigned int id = _shader->ID;
	const unsigned int tID = Renderer::instance()->GetTexture(_textureId)->ID;
	glUseProgram(id);
	glUniformMatrix4fv(glGetUniformLocation(id, "model"), 1, GL_TRUE, &model->buff[0]);
	Renderer::instance()->SetShaderVariables(id);
	glBindTexture(GL_TEXTURE_2D, tID);
	glUniform1i(glGetUniformLocation(_shader->ID, "tex0"), tID); //maybe this part is optioNAL
	Renderer::instance()->GetVAO()->Bind();
}
const unsigned int Sprite::ID()const { return _id; }