#include "RenderNode.h"
#include "../Graphics/Renderer.h"
#include "FBOComponent.h"
RenderNode::RenderNode() :
	BaseNode( Vec3(),  Renderer::instance()->WindowSizeVec3(), 0) {
	AddFBO();

}

//uses default image as background
RenderNode::RenderNode(const Vec3 pos, const Vec3 size, const float ang) :
	BaseNode(pos, size, ang){
	AddFBO();
}
void RenderNode::AddFBO() const {
	BaseNode::AddComponent<const FBOComponent>( new FBOComponent(_transform._scale.x, _transform._scale.y));
}
RenderNode::~RenderNode() {
	std::cout << "RENDER NODE DELETED\n";
}
void RenderNode::MakeModelMatrix(const Matrix4x4 trans, const Matrix4x4 scale, const Matrix4x4 rot) {
	//std::cout << "MMM from render node\n";
	Matrix4x4 nt, ns, nr;
	if (_inheritTransform[0])
		nt = Matrix4x4::TranslationMatrix(_transform._position) * trans;
	else
		nt = Matrix4x4::TranslationMatrix(_transform._position);

	if (_inheritTransform[1])
		ns = Matrix4x4::ScaleMatrix(_transform._scale) * scale;
	else
		ns = Matrix4x4::ScaleMatrix(_transform._scale);

	if (_inheritTransform[2])
		nr = Matrix4x4::RotationMatrix(_transform._angle.y) * rot;
	else
		nr = Matrix4x4::RotationMatrix(_transform._angle.y);

	for (int i = 0; i < _children->size(); ++i) {
		_children->at(i)->MakeModelMatrix(Matrix4x4(1.0f), Matrix4x4(1.0f), Matrix4x4(1.0f));
	}

	_model = nt * nr * ns;
}