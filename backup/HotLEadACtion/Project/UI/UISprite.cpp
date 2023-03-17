#include "UISprite.h"
#include "../Graphics/Renderer.h"
UIsprite::UIsprite() : Graphic() , Element(){}
UIsprite::UIsprite(const char* path, Vec3 pos, Vec3 size, float ang) :
	Graphic(path, pos, size, ang), Element(){


}

UIsprite::~UIsprite() {
	std::cout << "deleting uisprite \n";
}
void UIsprite::BeforeDraw() {
	Element* e = _parent;
	Matrix4x4 pOffset = Matrix4x4(0);
	while (e != NULL)
	{
		pOffset = pOffset * e->GetTransform();
		e = e->GetParent();
	}

	_shader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "transform"), 1, GL_TRUE, &(_transform * pOffset ).buff[0]);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "rotation"), 1, GL_TRUE, &_rotation.buff[0]);
	glUniformMatrix4fv(glGetUniformLocation(_shader->ID, "scale"), 1, GL_TRUE, &_scale.buff[0]);
	Renderer::instance()->SetShaderVariables(_shader);
	Renderer::instance()->GetTexture(_texId)->Bind();
	Renderer::instance()->GetTexture(_texId)->texUni(_shader, "tex0", 0);
	Renderer::instance()->GetVAO()->Bind();
}
void UIsprite::Draw() {
	BeforeDraw();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	AfterDraw();
}
void UIsprite::UpdateTransform(Matrix4x4 parent) {
	//_model[11] is the z value for translation
	//float z = _rect._position.z;
	//_rect._position.z = 0;
	//_model = Matrix4x4::TranslationMatrix(_rect._position) * parent;
	_transform = _transform * parent;
	for (int i = 0; i < _children->size(); ++i) {
		//_children->at(i)->UpdateTransform(_transform);
	}
	//_rect._position.z = z;
	//_model.buff[11] = z;
	//_model = _model * Matrix4x4::RotationMatrix(_rect._angle)
	//	* Matrix4x4::ScaleMatrix(Vec3(_rect._size.x, _rect._size.y, 1));
	//std::cout << " sprite z : " << _model.buff[11] << "\n";
}
Matrix4x4 UIsprite::GetTransform() { return _transform; }