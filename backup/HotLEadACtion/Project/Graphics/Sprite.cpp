
#include "Sprite.h"
#include "Renderer.h"
Sprite::Sprite(): Graphic() {
}
Sprite::Sprite(const char* path, Vec3 pos, Vec3 size, float ang): Graphic(path, pos, size, ang) {}
Sprite::~Sprite() {
	
}

void Sprite::BeforeDraw() {
	//std::cout << "CALLING BEFORE DRAW FROM -SPRITE-\n";
	_shader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "transform"), 1, GL_TRUE, &_transform.buff[0]);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "rotation"), 1, GL_TRUE, &_rotation.buff[0]);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "scale"), 1, GL_TRUE, &_scale.buff[0]);
	Renderer::instance()->SetShaderVariables(_shader);
	Renderer::instance()->GetTexture(_texId)->Bind();
	Renderer::instance()->GetTexture(_texId)->texUni(_shader, "tex0", 0);
	Renderer::instance()->GetVAO()->Bind();
}
void Sprite::Draw() {
	BeforeDraw();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	AfterDraw();
}