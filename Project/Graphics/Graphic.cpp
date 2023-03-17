#include "Graphic.h"
#include "Renderer.h"
Graphic::Graphic():BaseObject(){
	_texId = Renderer::instance()->LoadTexture("Assets/Textures/default.png");
	_shader = Renderer::instance()->GetShader(0);
	Renderer::instance()->AddGraphic(this);

}
Graphic::Graphic(const char* path, Vec3 pos, Vec3 size, float ang):BaseObject(pos, size, Vec3(0, ang, 0)){
	_texId = Renderer::instance()->LoadTexture(path);
	_shader = Renderer::instance()->GetShader(0);
	Renderer::instance()->AddGraphic(this);
}
Graphic::~Graphic() {
}

void Graphic::AfterDraw() {
	glBindVertexArray(0);
	Renderer::instance()->GetTexture(_texId)->Unbind();
	glUseProgram(0);
}
void Graphic::TryDraw() {
	if (!_visible) return;
	if (!_enabled) return;
	Draw();
	
}
void Graphic::Update(float deltaTime) {
	return;
}
Texture* Graphic::GetTexture() { return Renderer::instance()->GetTexture(_texId); }


//8 26 25 11