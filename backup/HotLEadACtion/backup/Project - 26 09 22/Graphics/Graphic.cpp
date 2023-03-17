#include "Graphic.h"
#include "Renderer.h"
Graphic::Graphic(){
	_rect = Graphic::MakeSPD(Vec3(0, 0, 0), Vec2(100, 100), 0);
	_texId = Renderer::instance()->LoadTexture("Textures/default.png");
	_shader = Renderer::instance()->GetShader(0);
	_model = Matrix4x4(1.0f);
	Renderer::instance()->AddGraphic(this);
}
Graphic::Graphic(const char* path, SpriteData spData): _rect(spData){
	_texId = Renderer::instance()->LoadTexture(path);
	_model = Matrix4x4(1.0f);
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


Matrix4x4 Graphic::MakeModelMatrix() {
	_model = Matrix4x4::TranslationMatrix(_rect._position)
		* Matrix4x4::RotationMatrix(_rect._angle)
		* Matrix4x4::ScaleMatrix(Vec3(_rect._size.x, _rect._size.y, 1));
	return _model;
}
Matrix4x4 Graphic::GetMatrix() {
	return _model;
}
SpriteData Graphic::GetSpriteData() {
	return _rect;
}
Texture* Graphic::GetTexture() { return Renderer::instance()->GetTexture(_texId); }
void Graphic::SetSize(Vec2 size) { _rect._size = size; }
void Graphic::SetPosition(Vec3 pos) { _rect._position = pos; }
void Graphic::SetAngle(float ang) { _rect._angle = ang; }

/// <summary>
/// Make Sprite Data, creates a struct that defines the model matrix of the sprite
/// </summary>
/// <param name="pos">x y z positions in pixel space</param>
/// <param name="size">width and height in pixel size</param>
/// <param name="ang">rotation in  radians</param>
/// <returns></returns>
SpriteData Graphic::MakeSPD(Vec3 pos, Vec2 size, float ang) {
	SpriteData spd;
	spd._position = pos;
	spd._size = size;
	spd._angle = ang;
	return spd;
}


//8 26 25 11