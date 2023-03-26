#include "RenderNode.h"
#include "../Graphics/Renderer.h"
#include "../Game/Game.h"
RenderNode::RenderNode():
	BaseObject(Vec3(), Renderer::instance()->WindowSizeVec3(), Vec3(0, 0, 0), Game::_world, 2) {


}

//uses default image as background
RenderNode::RenderNode(Vec3 pos, Vec3 size, float ang, BaseObject* parent): 
	BaseObject(pos, size, Vec3(0,ang,0), parent, 2){
	
}

void RenderNode::MakeModelMatrix(Matrix4x4 trans, Matrix4x4 scale, Matrix4x4 rot) {
	std::cout << "MMM from render node\n";
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
	for (int i = 0; i < _onMakeModelCalls->size(); ++i) {
		_onMakeModelCalls->at(i)->Execute();
	}
}
