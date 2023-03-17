#include "Graphic.h"
#include "Renderer.h"
Graphic::Graphic(){

	_transform = Matrix4x4(1);
	_rotation = Matrix4x4::RotationMatrix(0);
	_scale = Matrix4x4::ScaleMatrix(Vec3(50, 50, 1));
	_texId = Renderer::instance()->LoadTexture("Assets/Textures/default.png");
	_shader = Renderer::instance()->GetShader(0);
	Renderer::instance()->AddGraphic(this);
	_angle = 0;
}
Graphic::Graphic(const char* path, Vec3 pos, Vec3 size, float ang){
	_texId = Renderer::instance()->LoadTexture(path);
	_transform = Matrix4x4::TranslationMatrix(pos);
	_rotation = Matrix4x4::RotationMatrix(ang);
	_scale = Matrix4x4::ScaleMatrix(size);
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


/*Matrix4x4 Graphic::MakeModelMatrix() {
	_model = Matrix4x4::TranslationMatrix(_rect._position)
		* Matrix4x4::RotationMatrix(_rect._angle)
		* Matrix4x4::ScaleMatrix(Vec3(_rect._size.x, _rect._size.y, 1));
	//std::cout << "graphic z : " << _model.buff[11] << "\n";
	return _model;
}
*/

Texture* Graphic::GetTexture() { return Renderer::instance()->GetTexture(_texId); }
void Graphic::SetSize(Vec3 size) {_scale.SetScale(size);}
void Graphic::SetPosition(Vec3 pos) { _transform.SetTranslation(pos); }
void Graphic::SetAngle(float ang) { _rotation.SetRotation(ang); }
float Graphic::GetAngle() {
	return _angle;
}
Vec3 Graphic::GetPosition() {
	return _transform.GetPosition();
}
Vec3 Graphic::GetSize() {
	return _scale.GetSize();
}

//8 26 25 11