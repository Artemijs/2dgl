
#include "Sprite.h"
#include "Renderer.h"
namespace v1_5 {
	Sprite::Sprite() : Graphic() {
	}
	Sprite::Sprite(const char* path, Vec3 pos, Vec3 size, float ang, BaseObject* parent) : Graphic(path, pos, size, ang, parent) {}
	Sprite::~Sprite() {

	}

	void Sprite::BeforeDraw() {
		//std::cout << "CALLING BEFORE DRAW FROM -SPRITE-\n";
		_shader->Activate();
		glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "model"), 1, GL_TRUE, &_model.buff[0]);
		Renderer::instance()->SetShaderVariables(_shader->ID);
		Renderer::instance()->GetTexture(_texId)->Bind();
		Renderer::instance()->GetTexture(_texId)->texUni(_shader, "tex0", 0);
		Renderer::instance()->GetVAO()->Bind();
	}
	void Sprite::Draw() {
		BeforeDraw();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		AfterDraw();
	}
}


namespace v1_6 {
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
		v1_5::Renderer::instance()->SetShaderVariables(id);
		glBindTexture(GL_TEXTURE_2D, _textureId);
		//Renderer::instance()->GetTexture(_texId)->texUni(_shader, "tex0", 0);
		v1_5::Renderer::instance()->GetVAO()->Bind();
	}
};